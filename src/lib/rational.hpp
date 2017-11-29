#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>

#include "intx.hpp"

#ifdef HAVE_LIBGMPXX

#include "gmp.h"
#include "gmpxx.h"

typedef mpq_class rational;

intx get_num(const rational &r) {
    return r.get_num();
}
intx get_den(const rational &r) {
    return r.get_den();
}

#else // HAVE_LIBGMPXX

struct rational {
    intx a, b;

    rational(intx _a = 0, intx _b = 1) {
        a = _a;
        b = _b;

        intx g = gcd(a,b);
        a = a / g;
        b = b / g;

        if (b < 0) {
            a = -a;
            b = -b;
        }
    }

    rational(const rational &other) {
        a = other.a;
        b = other.b;
    }

    ~rational() {
    }

    rational& operator =(const rational &other) {
        a = other.a;
        b = other.b;
        return *this;
    }

    rational operator +(const rational &other) const {
        return rational(a * other.b + b * other.a, b * other.b);
    }

    rational operator -() const {
        return rational(-a, b);
    }

    rational operator -(const rational &other) const {
        return rational(a * other.b - b * other.a, b * other.b);
    }

    rational operator *(const rational &other) const {
        return rational(a * other.a, b * other.b);
    }

    rational operator /(const rational &other) const {
        return rational(a * other.b, b * other.a);
    }

    bool operator ==(const rational &other) const {
        return a * other.b == other.a * b;
    }

    bool operator !=(const rational &other) const {
        return a * other.b != other.a * b;
    }

    bool operator <(const rational &other) const {
        return a * other.b < other.a * b;
    }

    bool operator <=(const rational &other) const {
        return a * other.b <= other.a * b;
    }
};

std::ostream& operator <<(std::ostream &out, const rational &r) {
    if (r.a == 0) {
        out << "0";
    } else {
        if (r.b != 1) {
            out << "(";
        }
        out << r.a;
        if (r.b != 1) {
            out << ")/(";
            out << r.b;
            out << ")";
        }
    }
    return out;
}

intx get_num(const rational &r) {
    return r.a;
}
intx get_den(const rational &r) {
    return r.b;
}

#endif // HAVE_LIBGMPXX
#endif // _RATIONAL_H_
