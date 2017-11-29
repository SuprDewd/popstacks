// #include <bits/stdc++.h>
// using namespace std;
// template <class T> int size(const T &x) { return x.size(); }
// #define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
// #define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
// typedef pair<int, int> ii;
// typedef vector<int> vi;
// typedef vector<ii> vii;
// typedef long long ll;
// const int INF = 2147483647;

struct intx {
    static const int bits = 30;
    static const unsigned int base = 1U<<bits,
                              mask = base-1;
    int sign;
    vector<unsigned int> data;
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
ostream& operator <<(ostream &out, intx x) {
    if (x.sign < 0) out << "-";
    stack<int> S;
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

intx parse(string s) {
    bool neg = false;
    intx res;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i == 0 && s[i] == '-') {
            neg = true;
        } else {
            res = res * 10 + static_cast<int>(s[i] - '0');
        }
    }
    if (neg) {
        res = -res;
    }
    return res;
}

// intx get_rand(int d) {
//     intx res;
//     for (int i = 0; i < d; i++) {
//         res = res * intx::base + rand() % intx::base;
//     }
//     if (rand() % 2 == 0) {
//         res = -res;
//     }
//     return res;
// }
//
// int main() {
//     // intx a(9), b(8);
//     // cout << a << endl;
//     // cout << b << endl;
//     // cout << a+b << endl;
//     // cout << endl;
//     // cout << a-b << endl;
//     // cout << endl;
//     // cout << b-a << endl;
//     // cout << (b-a)+a << endl;
//     // cout << intx(9999) * intx(999) << endl;
//     // intx res = 1;
//     // for (int i = 0; i < 100; i++) {
//     //     res = res * 2;
//     // }
//     // cout << res << endl;
//
//     // intx a = parse("13876171263153172367812313461783461827451"),
//     //      b = parse("9123713612367123");
//     // cout << a << endl;
//     // cout << a + b << endl;
//     // cout << a * b << endl;
//     // cout << a / b << endl;
//     // cout << a % b << endl;
//     // cout << (a/b)*b + (a%b) << endl;
//
//     // srand(time(NULL));
//     //
//     // while (true) {
//     //     intx a = get_rand(10),
//     //         b = get_rand(5);
//     //     cout << "a = " << a << endl;
//     //     // cout << (a * b) % b << endl;
//     //     cout << "b = " << b << endl;
//     //     cout << "a/b = " << a/b << endl;
//     //     cout << "a%b = " << a%b << endl;
//     //     cout << "a/b*b+a%b = " << (a/b)*b+(a%b) << endl;
//     //     cout << endl;
//     //     // cout <<  << endl;
//     //     // assert(a == (a * b) / b);
//     //     assert(a == (a/b)*b+(a%b));
//     // }
//
//     return 0;
// }

