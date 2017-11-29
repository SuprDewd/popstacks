#ifndef _INTX_H_
#define _INTX_H_

#include <vector>
#include <sstream>
#include <string>
#include <iostream>

#ifdef HAVE_LIBGMPXX

#include "gmp.h"
#include "gmpxx.h"

typedef mpz_class intx;

#else // HAVE_LIBGMPXX

// struct intx {
//   intx() { normalize(1); }
//   intx(std::string n) {
//       if (n.empty()) n = "0";
//       if (n[0] == '-') sign = -1, n = n.substr(1);
//       for (int i = n.size() - 1; i >= 0; i -= intx::dcnt) {
//           unsigned int digit = 0;
//           for (int j = intx::dcnt - 1; j >= 0; j--) {
//               int idx = i - j;
//               if (idx < 0) continue;
//               digit = digit * 10 + (n[idx] - '0'); }
//           data.push_back(digit); }
//       normalize(sign);
//   }
//   intx(int n) : intx(std::to_string(n)) {
//       // std::stringstream ss;
//       // ss << n;
//       // intx(ss.str());
//       // sign = 1;
//       // if (n < 0) {
//       //     sign = -1;
//       //     n = -n;
//       // } else if (n == 0) {
//       //     data.push_back(0);
//       // } else {
//       //     while (n) {
//       //         data.push_back(n % radix);
//       //         n /= radix;
//       //     }
//       //     reverse(data.begin(), data.end());
//       // }
//   }
//   intx(const intx& other)
//     : sign(other.sign), data(other.data) { }
//   ~intx() {
//   }
//   intx& operator=(const intx &other) {
//       sign = other.sign;
//       data = other.data;
//       return *this;
//   }
//
//   int sign;
//   std::vector<unsigned int> data;
//   static const int dcnt = 9;
//   static const unsigned int radix = 1000000000U;
//   int size() const { return data.size(); }
//   void init(std::string n) {
//   }
//   intx& normalize(int nsign) {
//     if (data.empty()) data.push_back(0);
//     for (int i = data.size() - 1; i > 0 && data[i] == 0; i--)
//       data.erase(data.begin() + i);
//     sign = data.size() == 1 && data[0] == 0 ? 1 : nsign;
//     return *this; }
//
//   std::string to_string() const {
//       std::stringstream ss; ss << *this; return ss.str(); }
//   bool operator <(const intx& b) const {
//     if (sign != b.sign) return sign < b.sign;
//     if (size() != b.size())
//       return sign == 1 ? size() < b.size() : size() > b.size();
//     for (int i = size() - 1; i >= 0; i--)
//       if (data[i] != b.data[i])
//         return sign == 1 ? data[i] < b.data[i]
//                          : data[i] > b.data[i];
//     return false; }
//   bool operator ==(const intx& b) const {
//       return !(*this < b) && !(b < *this);
//   }
//   bool operator !=(const intx& b) const {
//       return (*this < b) || (b < *this);
//   }
//   bool operator <=(const intx& b) const {
//       return !(b < *this);
//   }
//   intx operator -() const {
//     intx res(*this); res.sign *= -1; return res; }
//   friend intx abs(const intx &n) { return n < 0 ? -n : n; }
//   intx operator +(const intx& b) const {
//     if (sign > 0 && b.sign < 0) return *this - (-b);
//     if (sign < 0 && b.sign > 0) return b - (-*this);
//     if (sign < 0 && b.sign < 0) return -((-*this) + (-b));
//     intx c; c.data.clear();
//     unsigned long long carry = 0;
//     for (int i = 0; i < size() || i < b.size() || carry; i++) {
//       carry += (i < size() ? data[i] : 0ULL) +
//         (i < b.size() ? b.data[i] : 0ULL);
//       c.data.push_back(carry % intx::radix);
//       carry /= intx::radix; }
//     return c.normalize(sign); }
//   intx operator -(const intx& b) const {
//     if (sign > 0 && b.sign < 0) return *this + (-b);
//     if (sign < 0 && b.sign > 0) return -(-*this + b);
//     if (sign < 0 && b.sign < 0) return (-b) - (-*this);
//     if (*this < b) return -(b - *this);
//     intx c; c.data.clear();
//     long long borrow = 0;
//     for (int i = 0; i < size(); i++) {
//       borrow = data[i] - borrow
//                        - (i < b.size() ? b.data[i] : 0ULL);
//       c.data.push_back(borrow < 0 ? intx::radix + borrow
//                                   : borrow);
//       borrow = borrow < 0 ? 1 : 0; }
//     return c.normalize(sign); }
//   intx operator *(const intx& b) const {
//     intx c; c.data.assign(size() + b.size() + 1, 0);
//     for (int i = 0; i < size(); i++) {
//       long long carry = 0;
//       for (int j = 0; j < b.size() || carry; j++) {
//         if (j < b.size())
//           carry += (long long)data[i] * b.data[j];
//         carry += c.data[i + j];
//         c.data[i + j] = carry % intx::radix;
//         carry /= intx::radix; } }
//     return c.normalize(sign * b.sign); }
//   friend std::pair<intx,intx> divmod(const intx& n, const intx& d) {
//     assert(!(d.size() == 1 && d.data[0] == 0));
//     intx q, r; q.data.assign(n.size(), 0);
//     for (int i = n.size() - 1; i >= 0; i--) {
//       r.data.insert(r.data.begin(), 0);
//       r = r + n.data[i];
//       long long k = 0;
//       if (d.size() < r.size())
//         k = (long long)intx::radix * r.data[d.size()];
//       if (d.size() - 1 < r.size()) k += r.data[d.size() - 1];
//       k /= d.data.back();
//       r = r - abs(d) * k;
//       // if (r < 0) for (ll t = 1LL << 62; t >= 1; t >>= 1) {
//       //     intx dd = abs(d) * t;
//       //     while (r + dd < 0) r = r + dd, k -= t; }
//       while (r < 0) r = r + abs(d), k--;
//       q.data[i] = k; }
//     return std::pair<intx, intx>(q.normalize(n.sign * d.sign), r); }
//   intx operator /(const intx& d) const {
//     return divmod(*this,d).first; }
//   intx operator %(const intx& d) const {
//     return divmod(*this,d).second * sign; }
//
//     friend std::ostream& operator <<(std::ostream& outs, const intx& n);
// };
//
// std::ostream& operator <<(std::ostream& outs, const intx& n) {
//     if (n.sign < 0) outs << '-';
//     bool first = true;
//     for (int i = n.size() - 1; i >= 0; i--) {
//       if (first) outs << n.data[i], first = false;
//       else {
//         unsigned int cur = n.data[i];
//         std::stringstream ss; ss << cur;
//         std::string s = ss.str();
//         int len = s.size();
//         while (len < intx::dcnt) outs << '0', len++;
//         outs << s; } }
//     return outs; }

struct intx {
    static const int bits = 30;
    static const unsigned int base = 1U<<bits,
                              mask = base-1;
    int sign;
    std::vector<unsigned int> data;
    intx() : sign(1) {
    }
    intx(int n) : sign(1) {
        if (n < 0) {
            sign = -1;
            n = -n;
        }
        while (n) {
            data.push_back(n & mask);
            n >>= bits;
        }
    }
    intx operator -() const {
        intx res;
        res.data = data;
        res.sign = -sign;
        return res;
    }
    bool operator <(const intx &other) const {
        if (sign != other.sign) {
            return sign < other.sign;
        }
        bool res = false;
        if (data.size() != other.data.size()) {
            res = data.size() < other.data.size();
            if (sign < 0) res = !res;
        } else {
            for (size_t i = data.size() - 1; i < data.size(); --i) {
                if (data[i] != other.data[i]) {
                    res = data[i] < other.data[i];
                    if (sign < 0) res = !res;
                    break;
                }
            }
        }
        return res;
    }
    bool operator ==(const intx &other) const {
        return !(*this < other) && !(other < *this);
    }
    bool operator !=(const intx &other) const {
        return (*this < other) || (other < *this);
    }
    bool operator <=(const intx &other) const {
        return !(other < *this);
    }
    intx abs() const {
        intx res(*this);
        res.sign = 1;
        return res;
    }
    intx uadd(const intx &other) const {
        intx res;
        unsigned int carry = 0;
        for (size_t i = 0; i < data.size() || i < other.data.size() || carry; ++i) {
            if (i < data.size()) carry += data[i];
            if (i < other.data.size()) carry += other.data[i];
            res.data.push_back(carry & mask);
            carry >>= bits;
        }
        return res;
    }
    intx ussub(const intx &other) const {
        intx res;
        unsigned int carry = 0, here;
        for (size_t i = 0; i < data.size() || i < other.data.size(); ++i) {
            here = -carry;
            carry = 0;
            if (i < data.size()) here += data[i];
            if (i < other.data.size()) here -= other.data[i];
            if (here & ~mask) {
                carry = 1;
                here += base;
            }
            res.data.push_back(here & mask);
        }
        assert(!carry);
        while (!res.data.empty() && res.data.back() == 0) res.data.pop_back();
        return res;
    }
    intx usub(const intx &other) const {
        intx res;
        if (this->abs() < other.abs()) {
            res = other.ussub(*this);
            res.sign = -res.sign;
        } else {
            res = ussub(other);
        }
        return res;
    }
    intx operator +(const intx &other) const {
        intx res = sign == other.sign ? uadd(other) : usub(other);
        if (sign == -1) res.sign = -res.sign;
        return res;
    }
    intx operator -(const intx &other) const {
        intx res = sign == other.sign ? usub(other) : uadd(other);
        if (sign == -1) res.sign = -res.sign;
        return res;
    }
    intx operator *(const intx &other) const {
        intx res;
        res.data.resize(data.size() + other.data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            unsigned long long carry = 0;
            for (size_t j = 0; j < other.data.size() || carry; ++j) {
                carry += res.data[i+j];
                if (j < other.data.size()) {
                    carry += (unsigned long long)data[i] * other.data[j];
                }
                res.data[i+j] = carry & mask;
                carry >>= bits;
            }
        }
        while (!res.data.empty() && res.data.back() == 0) res.data.pop_back();
        if (!res.data.empty()) res.sign = sign * other.sign;
        return res;
    }
    intx operator /(const intx &other) const {
        intx cur, res;
        for (size_t i = data.size() - 1; i < data.size(); --i) {
            cur.data.insert(cur.data.begin(), data[i]);
            unsigned int lo = 0,
                         hi = mask,
                         want = 0;
            while (lo <= hi) {
                unsigned int mid = (lo+hi)/2;
                if (cur < other.abs() * mid) {
                    hi = mid-1;
                } else {
                    lo = mid+1;
                    want = mid;
                }
            }
            cur = cur - other.abs() * want;
            res.data.insert(res.data.begin(), want);
        }
        while (!res.data.empty() && res.data.back() == 0) res.data.pop_back();
        if (!res.data.empty()) res.sign = sign * other.sign;
        return res;
    }
    intx operator %(const intx &other) const {
        intx cur;
        for (size_t i = data.size() - 1; i < data.size(); --i) {
            cur.data.insert(cur.data.begin(), data[i]);
            unsigned int lo = 0,
                         hi = mask,
                         want = 0;
            while (lo <= hi) {
                unsigned int mid = (lo+hi)/2;
                if (cur < other.abs() * mid) {
                    hi = mid-1;
                } else {
                    lo = mid+1;
                    want = mid;
                }
            }
            cur = cur - other.abs() * want;
        }
        if (!cur.data.empty()) cur.sign = sign;
        return cur;
    }
};
std::ostream& operator <<(std::ostream &out, intx x) {
    if (x.sign < 0) out << "-";
    std::stack<int> S;
    x = x.abs();
    while (x != 0) {
        intx cur = x % 10;
        x = x / 10;
        S.push(cur.data.empty() ? 0 : cur.data[0]);
    }
    if (S.empty()) {
        out << "0";
    }
    while (!S.empty()) {
        out << S.top();
        S.pop();
    }
    return out;
}

// intx parse(std::string s) {
//     bool neg = false;
//     intx res;
//     for (size_t i = 0; i < s.size(); ++i) {
//         if (i == 0 && s[i] == '-') {
//             neg = true;
//         } else {
//             res = res * 10 + static_cast<int>(s[i] - '0');
//         }
//     }
//     if (neg) {
//         res = -res;
//     }
//     return res;
// }

intx gcd(intx a, intx b) {
    return b == 0 ? a : gcd(b, a % b);
}

intx lcm(intx a, intx b) {
    return a / gcd(a,b) * b;
}

#endif // HAVE_LIBGMPXX
#endif // _INTX_H_
