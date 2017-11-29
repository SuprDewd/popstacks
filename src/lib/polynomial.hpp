#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <vector>
#include <string>
#include <sstream>

#include "intx.hpp"

// #include "gmp.h"
// #include "gmpxx.h"

struct polynomial {
    std::vector<intx> c;

    polynomial() {
    }

    polynomial(intx t) {
        c.push_back(t);
        _clean();
    }

    polynomial(std::vector<intx> _c) : c(_c) {
        _clean();
    }

    polynomial(const polynomial &other) : c(other.c) {
    }

    polynomial& operator =(const polynomial &other) {
        c = other.c;
        return *this;
    }

    ~polynomial() {
    }

    void _clean() {
        while (!c.empty() && c.back() == 0) {
            c.pop_back();
        }
    }

    void _request(size_t l) {
        if (c.size() < l) {
            c.resize(l);
        }
    }

    polynomial operator +(const polynomial &other) const {
        polynomial res;
        for (size_t i = 0; i < c.size() || i < other.c.size(); ++i) {
            intx cur = 0;
            if (i < c.size()) cur = cur + c[i];
            if (i < other.c.size()) cur = cur + other.c[i];
            res.c.push_back(cur);
        }
        res._clean();
        return res;
    }

    polynomial operator -() const {
        polynomial res(c);
        for (size_t i = 0; i < c.size(); ++i) {
            res.c[i] = -res.c[i];
        }
        return res;
    }

    polynomial operator -(const polynomial &other) const {
        polynomial res;
        for (size_t i = 0; i < c.size() || i < other.c.size(); ++i) {
            intx cur = 0;
            if (i < c.size()) cur = cur + c[i];
            if (i < other.c.size()) cur = cur - other.c[i];
            res.c.push_back(cur);
        }
        res._clean();
        return res;
    }

    polynomial operator *(const polynomial &other) const {
        polynomial res;
        res._request(c.size() + other.c.size());
        for (size_t i = 0; i < c.size(); ++i) {
            for (size_t j = 0; j < other.c.size(); ++j) {
                res.c[i + j] = res.c[i + j] + c[i] * other.c[j];
            }
        }
        res._clean();
        return res;
    }

    polynomial operator *(const intx &other) const {
        polynomial res(c);
        for (size_t i = 0; i < c.size(); ++i) {
            res.c[i] = res.c[i] * other;
        }
        res._clean();
        return res;
    }

    bool operator ==(const polynomial &other) const {
        if (c.size() != other.c.size()) {
            return false;
        }
        for (size_t i = 0; i < c.size(); ++i) {
            if (c[i] != other.c[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator !=(const polynomial &other) const {
        return !(*this == other);
    }

    bool operator <(const polynomial &other) const {
        polynomial res = *this - other;
        return !res.c.empty() && res.c.back() < 0;
    }

    bool operator <=(const polynomial &other) const {
        polynomial res = *this - other;
        return res.c.empty() || res.c.back() < 0;
    }

    std::string to_string(std::string var) const {
        std::stringstream ss;
        bool first = true;
        for (size_t i = c.size() - 1; i < c.size(); --i) {
            if (c[i] == 0) {
                continue;
            }
            intx cur = c[i];
            if (!first) {
                if (cur < 0) {
                    ss << " - ";
                    cur = -cur;
                } else {
                    ss << " + ";
                }
            }
            if (first) {
                if (cur == -1) {
                    ss << "-";
                    cur = -cur;
                }
            }
            if (cur != 1) {
                ss << cur;
            }
            if (cur == 1 && i == 0) {
                ss << 1;
            }
            if (cur != 1 && i != 0) {
                ss << "*";
            }
            if (i != 0) {
                ss << var;
                if (i != 1) {
                    ss << "^";
                    ss << i;
                }
            }
            first = false;
        }

        if (first) {
            ss << 0;
        }

        return ss.str();
    }

    static polynomial X(int k) {
        polynomial res;
        res._request(k+1);
        res.c[k] = 1;
        return res;
    }

    static polynomial zero() {
        polynomial res;
        return res;
    }

    static polynomial one() {
        return X(0);
    }
};

std::ostream& operator <<(std::ostream &out, const polynomial &p) {
    return out << p.to_string("x");
}

#endif
