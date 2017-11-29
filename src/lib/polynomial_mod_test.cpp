#include <bits/stdc++.h>
#include "gmp.h"
#include "gmpxx.h"
// #include "polynomial_mod.hpp"
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

// using namespace polynomial_mod;

typedef std::vector<mpq_class> pol;

void clean(pol &p) {
    while (!p.empty() && p.back() == 0) {
        p.pop_back();
    }
}

void pdiv(pol &a, const pol &b) {
    assert(b.size() != 0);
    pol res;
    for (size_t i = a.size() - 1; i < a.size() && i + 1 >= b.size(); --i) {
        res.resize(i - b.size() + 2);
        res[i - b.size() + 1] = a[i] / b.back();
        for (size_t j = 0; j < b.size(); ++j) {
            a[i + j - b.size() + 1] -= (a[i] / b.back()) * b[j];
        }
        assert(a[i] == 0);
    }
    clean(res);
}

void pmod(pol &a, const pol &b) {
    assert(b.size() != 0);
    for (size_t i = a.size() - 1; i < a.size() && i + 1 >= b.size(); --i) {
        for (size_t j = 0; j < b.size(); ++j) {
            a[i + j - b.size() + 1] -= (a[i] / b.back()) * b[j];
        }
        assert(a[i] == 0);
    }
    clean(a);
}

void simplify(pol &a) {
    if (a.size() == 0) {
        return;
    }
    mpz_class g = a.back().get_den();
    for (size_t i = 0; i+1 < a.size(); ++i) {
        if (a[i].get_den() != 0) {
            g = lcm(g, a[i].get_den());
        }
    }
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] *= g;
        assert(a[i].get_den() == 1);
    }
    g = a.back().get_num();
    for (size_t i = 0; i+1 < a.size(); ++i) {
        if (a[i].get_num() != 0) {
            g = gcd(g, a[i].get_num());
        }
    }
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] /= g;
        assert(a[i].get_den() == 1);
    }
}

void gcd(pol &a, pol &b) {
    while (!b.empty()) {
        pmod(a, b);
        simplify(a);
        a.swap(b);
    }
}

void simplify(pol &a, pol &b) {
    mpz_class g = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        assert(a[i].get_den() == 1);
        if (g == 0) {
            g = a[i];
        } else if (a[i].get_num() != 0) {
            g = gcd(g, a[i].get_num());
        }
    }
    for (size_t i = 0; i < b.size(); ++i) {
        assert(b[i].get_den() == 1);
        if (g == 0) {
            g = b[i];
        } else if (b[i].get_num() != 0) {
            g = gcd(g, b[i].get_num());
        }
    }
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] /= g;
        assert(a[i].get_den() == 1);
    }
    for (size_t i = 0; i < b.size(); ++i) {
        b[i] /= g;
        assert(b[i].get_den() == 1);
    }
}

int main() {
    pol p = {0,7,19,10,7,5},
        q = {0,7,-9,-10,7,5};

    rep(i,0,size(p)) p[i] *= 2;
    rep(i,0,size(q)) q[i] *= 2;

    cout << "(";
    rep(i,0,size(p)) {
        if (i != 0) cout << "+";
        cout << p[i] << "*x^" << i;
    }
    cout << ")/(";
    rep(i,0,size(q)) {
        if (i != 0) cout << "+";
        cout << q[i] << "*x^" << i;
    }
    cout << ")" << endl;

    gcd(p, q);
    // pmod(p, q);
    cout << "(";
    rep(i,0,size(p)) {
        if (i != 0) cout << "+";
        cout << p[i] << "*x^" << i;
    }
    cout << ")" << endl;

    return 0;
}

