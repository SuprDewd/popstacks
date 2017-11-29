#ifndef _POLYNOMIAL_MOD_H_
#define _POLYNOMIAL_MOD_H_

namespace polynomial_mod {
    typedef std::vector<mpq_class> polynomial;

    void clean(polynomial &p) {
        while (!p.empty() && p.back() == 0) {
            p.pop_back();
        }
    }

    // polynomial add(polynomial a, polynomial b) {
    // }
    //
    // polynomial mul(polynomial a, polynomial b) {
    // }

    void pmod(polynomial &a, const polynomial &b) {
        assert(b.size() != 0);
        // a / b
        for (size_t i = a.size() - 1; i < a.size() && i + 1 >= b.size(); --i) {
            // (t * x ^ k) * (b.back() * x^(b.size() - 1)) = a[i] * x^i
            // k = i - b.size() + 1
            // t = a[i] / b.back()

            // here = ;
            // a = a - here * b;

            for (size_t j = 0; j < b.size(); ++j) {
                a[i + j - b.size() + 1] -= (a[i] / b.back()) * b[j];
                // a = a -  * x ^ (i + j - b.size() + 1)
            }

            // res = res + here
        }

        clean(a);
    }

    void simplify(polynomial &a) {
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

    void gcd(polynomial &a, polynomial &b) {
        while (!b.empty()) {
            pmod(a, b);
            simplify(a);
            a.swap(b);
        }
    }
};

#endif
