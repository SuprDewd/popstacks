#ifndef _POLYNOMIAL_RATIONAL_H_
#define _POLYNOMIAL_RATIONAL_H_

#include <iostream>

#include "intx.hpp"
#include "rational.hpp"
#include "polynomial.hpp"

namespace pgcd {
    typedef std::vector<rational> pol;

    void clean(pol &p) {
        while (!p.empty() && p.back() == rational(0,1)) {
            p.pop_back();
        }
    }

    void pdiv(pol &a, const pol &b) {
        assert(b.size() != 0);
        pol res(b.size() <= a.size() ? a.size() - b.size() + 1 : 0);
        for (size_t i = a.size() - 1; i < a.size() && i + 1 >= b.size(); --i) {
            res[i - b.size() + 1] = a[i] / b.back();
            for (size_t j = 0; j < b.size(); ++j) {
                a[i + j - b.size() + 1] = a[i + j - b.size() + 1] - (a[i] / b.back()) * b[j];
            }
            assert(a[i] == rational(0,1));
        }
        clean(res);
        a.swap(res);
    }

    void pmod(pol &a, const pol &b) {
        assert(b.size() != 0);
        for (size_t i = a.size() - 1; i < a.size() && i + 1 >= b.size(); --i) {
            for (size_t j = 0; j < b.size(); ++j) {
                a[i + j - b.size() + 1] = a[i + j - b.size() + 1] - (a[i] / b.back()) * b[j];
            }
            assert(a[i] == rational(0,1));
        }
        clean(a);
    }

    void simplify(pol &a) {
        if (a.size() == 0) {
            return;
        }
        intx g = get_den(a.back());
        for (size_t i = 0; i+1 < a.size(); ++i) {
            if (get_den(a[i]) != 0) {
                g = lcm(g, get_den(a[i]));
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = a[i] * g;
            assert(get_den(a[i]) == 1);
        }
        g = get_num(a.back());
        for (size_t i = 0; i+1 < a.size(); ++i) {
            if (get_num(a[i]) != 0) {
                g = gcd(g, get_num(a[i]));
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = a[i] / g;
            assert(get_den(a[i]) == 1);
        }
    }

    void gcd(pol &a, pol &b) {
        while (!b.empty()) {
            pmod(a, b);
            simplify(a);
            a.swap(b);
        }
        simplify(a);
    }

    void simplify(pol &a, pol &b) {
        intx g = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            assert(get_den(a[i]) == 1);
            if (g == 0) {
                g = get_num(a[i]);
            } else if (get_num(a[i]) != 0) {
                g = gcd(g, get_num(a[i]));
            }
        }
        for (size_t i = 0; i < b.size(); ++i) {
            assert(get_den(b[i]) == 1);
            if (g == 0) {
                g = get_num(b[i]);
            } else if (get_num(b[i]) != 0) {
                g = gcd(g, get_num(b[i]));
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = a[i] / g;
            assert(get_den(a[i]) == 1);
        }
        for (size_t i = 0; i < b.size(); ++i) {
            b[i] = b[i] / g;
            assert(get_den(b[i]) == 1);
        }
    }
};

struct polynomial_rational {
    polynomial a, b;

    polynomial_rational(polynomial _a = polynomial::zero(), polynomial _b = polynomial::one()) {

        pgcd::pol ga(_a.c.size()), rem(_a.c.size()), gb(_b.c.size()), tmpb(_b.c.size());
        for (size_t i = 0; i < _a.c.size(); ++i) ga[i] = rem[i] = _a.c[i];
        for (size_t i = 0; i < _b.c.size(); ++i) gb[i] = tmpb[i] = _b.c[i];

        pgcd::gcd(rem, tmpb);
        pgcd::pdiv(ga, rem);
        pgcd::pdiv(gb, rem);
        pgcd::simplify(ga, gb);

        a.c.resize(ga.size());
        for (size_t i = 0; i < ga.size(); ++i) a.c[i] = get_num(ga[i]);
        b.c.resize(gb.size());
        for (size_t i = 0; i < gb.size(); ++i) b.c[i] = get_num(gb[i]);

        if (b < polynomial::zero()) {
            a = -a;
            b = -b;
        }

        // assert(a * _b == _a * b); // TODO: Remove
    }

    polynomial_rational(const polynomial_rational &other) {
        a = other.a;
        b = other.b;
    }

    ~polynomial_rational() {
    }

    polynomial_rational& operator =(const polynomial_rational &other) {
        a = other.a;
        b = other.b;
        return *this;
    }

    polynomial_rational operator +(const polynomial_rational &other) const {
        return polynomial_rational(a * other.b + b * other.a, b * other.b);
    }

    polynomial_rational operator -() const {
        return polynomial_rational(-a, b);
    }

    polynomial_rational operator -(const polynomial_rational &other) const {
        return polynomial_rational(a * other.b - b * other.a, b * other.b);
    }

    polynomial_rational operator *(const polynomial_rational &other) const {
        return polynomial_rational(a * other.a, b * other.b);
    }

    polynomial_rational operator /(const polynomial_rational &other) const {
        return polynomial_rational(a * other.b, b * other.a);
    }

    bool operator ==(const polynomial_rational &other) const {
        return a * other.b == other.a * b;
    }

    bool operator !=(const polynomial_rational &other) const {
        return a * other.b != other.a * b;
    }

    bool operator <(const polynomial_rational &other) const {
        return a * other.b < other.a * b;
    }

    bool operator <=(const polynomial_rational &other) const {
        return a * other.b <= other.a * b;
    }

    static polynomial_rational zero() {
        return polynomial_rational(polynomial::zero(), polynomial::one());
    }

    static polynomial_rational one() {
        return polynomial_rational(polynomial::one(), polynomial::one());
    }
};

std::ostream& operator <<(std::ostream &out, const polynomial_rational &r) {
    if (r.a == polynomial::zero()) {
        out << "0";
    } else {
        if (r.b != polynomial::one()) {
            out << "(";
        }
        out << r.a;
        if (r.b != polynomial::one()) {
            out << ")/(";
            out << r.b;
            out << ")";
        }
    }
    return out;
}

#endif
