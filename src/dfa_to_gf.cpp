#include <bits/stdc++.h>

// template <class T>
// T one() { return T(1); }
// template <class T>
// T zero() { return T(0); }
//
// template <class T>
// T gcd(T a, T b) {
//     return b == zero<T>() ? a : gcd(b, a % b);
// }


// #include "gmp.h"
// #include "gmpxx.h"

#include "lib/dfa.hpp"
// #include "lib/rational.hpp"
#include "lib/polynomial.hpp"
#include "lib/polynomial_rational.hpp"

// template <> mpq_class one<mpq_class>() { return mpq_class(1); }
// template <> polynomial<mpq_class> one<polynomial<mpq_class> >() { return polynomial<mpq_class>(mpq_class(1)); }
//
// template <> mpq_class zero<mpq_class>() { return mpq_class(0); }
// template <> polynomial<mpq_class> zero<polynomial<mpq_class> >() { return polynomial<mpq_class>(); }

// template <class T>
// polynomial<T> gcd(polynomial<T> a, polynomial<T> b) {
//     return b == polynomial<T>::zero() ? a : gcd(b, a % b);
// }

#include "lib/matrix.hpp"
#include "lib/intx.hpp"
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF = 2147483647;
// typedef long long ll;
// typedef intx ll;
// typedef rational<ll> R;
// typedef mpq_class R;
// typedef polynomial<R> P;
// typedef rational<P> PR;

int main() {

    // pgcd::pol a = {0,1}, b={1};
    // pgcd::pdiv(a, b);
    // for (size_t i = 0; i < a.size(); ++i) {
    //     cout << a[i] << " ";
    // }
    // cout <<endl;

    // cout << polynomial_rational(polynomial::X(1), polynomial::one()) << endl;
    // return 0;

    // cout << PR::one() + P::X(1) << endl;
    // cout << PR::one() + PR(P::X(1)) << endl;
    // PR cur(P::X(1), P::X(0));
    // cout << cur << endl;

    dfa d = input_dfa(cin);

    matrix mat(d.n, d.n+1);
    for (int i = 0; i < d.n; i++) {
        // s_i = 
        mat(i, i) = mat(i, i) + polynomial_rational::one();
        iter(it,d.trans[i]) {
            // x * s_{*it} + 
            mat(i, it->second) = mat(i, it->second) - polynomial::X(1);
        }
        if (d.term.find(i) != d.term.end()) {
            // + 1
            mat(i, d.n) = mat(i, d.n) + polynomial::one();
        }
    }

    // for (int i = 0; i < d.n; i++) {
    //     for (int j = 0; j <= d.n; j++) {
    //         cout << mat(i,j) << "\t";
    //     }
    //     cout << endl;
    // }

    polynomial_rational det;
    int rank;
    mat = mat.rref(det, rank);

    // cout << endl;
    // cout << det << " " << rank << endl;
    // cout << endl;

    // cout << PR::one() - P::X(1) << endl;
    // cout << PR::one() / (PR::one() - P::X(1)) << endl;
    // PR cur = (PR::one() / (PR::one() - P::X(1))) * (PR::one() - P::X(1));
    // cout << cur << endl;

    // P a = cur.a,
    //   b = cur.b;
    //
    // P g = gcd(a,b);
    //
    // cout << a/g << endl;
    // cout << b/g << endl;
    // cout << g << endl;

    // mat.mul_row(1, );

    // mat.
    // cout << endl;
    // mat.add_row(0, 1, polynomial::X(1));
    // mat.add_row(0, 3, polynomial::X(1));
    // mat.mul_row(1, polynomial_rational::one() / (polynomial::one() - polynomial::X(1)));
    //
    // for (int i = 0; i < d.n; i++) {
    //     for (int j = 0; j <= d.n; j++) {
    //         cout << mat(i,j) << "\t";
    //     }
    //     cout << endl;
    // }

    cout << mat(d.start, d.n) / polynomial::X(1) << endl; // NOTE: The division by x at the end is only for the popstacks GF

    // polynomial_rational a = -polynomial_rational(polynomial::X(1)) + polynomial_rational::one(),
    //                     b = polynomial::one() / (polynomial::one() - polynomial::X(1));
    //
    // cout << a << endl;
    // cout << b << endl;
    // cout << a*b << endl;

    return 0;
}

