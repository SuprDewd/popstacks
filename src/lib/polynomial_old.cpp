#include <bits/stdc++.h>

#include "polynomial.hpp"
#include "rational.hpp"
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF = 2147483647;

typedef rational<ll> R;
typedef polynomial<R> P;

int main() {
    // P p = 
    //     P::X(7) * 8 +
    //     P::X(5) * (-2) +
    //     P::X(4) * 4 +
    //     P::X(0) * 1;
    //
    // P q = 
    //     P::X(3) * 5 +
    //     P::X(1) * 4 +
    //     P::X(0) * (-3);
    //
    // cout << "p = " << p << endl;
    // cout << "q = " << q << endl;
    //
    // P a = p/q,
    //   b = p%q;
    //
    // // cout << "p/q = " << a << endl;
    // // cout << "p%q = " << b << endl;
    // // cout << "(p/q)*q = " << a*q << endl;
    // // cout << "(p/q)*q+(p%q) = " << (a*q+b - p == R(0,1)) << endl;
    //
    // cout << p << endl;
    // cout << q << endl;
    // cout << gcd(p,q) << endl;

    P p = 
        P::X(2) * 1 +
        P::X(1) * 7 +
        P::X(0) * 6;

    P q = 
        P::X(2) * 1 +
        P::X(1) * (-5) +
        P::X(0) * (-6);

    cout << p << endl;
    cout << q << endl;

    cout << gcd(p,q) << endl;

    // p = p % q;
    // cout << p << endl;
    //
    // swap(p,q);
    //
    // p = p % q;
    // cout << p << endl;

    return 0;
}

