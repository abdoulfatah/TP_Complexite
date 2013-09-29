/*
 * @File algo_naif.cxx
 *
 * @Author p1002650
 *
 * @Date 14-09-2013
 *
 */

#include <iostream>
#include <sstream>
#include <limits>       // int max value
#include <algorithm>    // max()

#include "sous-sequence_max.h"

using namespace std;

namespace algo {

    int algo_naif(int * T, unsigned n) {
        int max_sum = numeric_limits<int>::min();
        for (unsigned i(0); i < n; ++i) {
            for (unsigned j(i); j < n; ++j) {
                int sum (T[i]);
                for (unsigned k(i+1); k < j; ++k)
                    sum += T[k];
                if (sum > max_sum)
                    max_sum = sum;
            }
        }
        return max_sum;
    }

    int algo_moins_naif(int * T, unsigned n) {
        int max_sum = numeric_limits<int>::min();
        for (unsigned i(0); i < n; ++i) {
            int sum (0);
            for (unsigned j(i); j < n; ++j) {
                sum += T[j];
                if (sum > max_sum)
                    max_sum = sum;
            }
        }
        return max_sum;
    }

    int * tab;
    int algo_div(int * T, unsigned n) {
        tab = T;
        return algo_div_impl(0, n);
    }

    int algo_div_impl(int k, int l) {
        int sz = l - k;
        if (sz == 1) {
            return tab[k];
        }
        else if (sz == 2) {
            return max(max(tab[k], tab[k+1]), tab[k] + tab[k+1]);
        }

        int sum_0, sum_1, sum_2, sum_3, sum_4, sum_tmp;
        int j = k + (sz / 2);

        sum_1 = algo_div_impl(k, j);
        sum_2 = algo_div_impl(j+1, l);

        // sous-sequence terminant par le pivot (tab[j])
        sum_3 = sum_tmp = tab[j];
        for (int i(j-1); i >= k; --i) {
            sum_tmp = sum_tmp + tab[i];
            if (sum_tmp > sum_3)
                sum_3 = sum_tmp;
        }

        // sous-sequence debutant par le pivot (tab[j])
        sum_4 = sum_tmp = tab[j];
        for (int i(j+1); i < l; ++i) {
            sum_tmp = sum_tmp + tab[i];
            if (sum_tmp > sum_4)
                sum_4 = sum_tmp;
        }

        sum_0 = sum_3 + sum_4 - tab[j];

        return max(max(sum_0, sum_1), sum_2);

    }

    int algo_incr(int * T, unsigned n) {
        int sum_max(T[0]);
        int sum_1(0);
        int sum_2(0);

        for (unsigned i(1); i < n; ++i) {
            sum_1 += T[i];
            sum_2 += T[i];
            if (sum_2 < 0)
                sum_2 = 0;
            if (sum_1 > 0) {
                sum_max += sum_1;
                sum_1 = 0;
                sum_2 = 0;
            }
            if (sum_2 > sum_max) {
                sum_max = sum_2;
                sum_1 = 0;
                sum_2 = 0;
            }
        }

        return sum_max;
    }

}

int test_asymptote() {
    unsigned n_max = 50000;
    unsigned step = n_max / 10;
    clock_t start, end;
    int * T = new int [n_max];
    unsigned start_index = 0;
    srand(time(NULL));

    cout << "n;secondes" << endl;
    for (unsigned i(1); i <= n_max/step; ++i) {
        unsigned n = i * step;

        // generate random array of n integers from -99 to 99
        for (unsigned j(start_index); j < n; ++j) {
            int sign = rand() % 2;
            int x = rand() % 100;
            T[j] = sign ? -x : x;
        }
        start_index = n;

        cout << n << ";";
        start = clock();
        algo::algo_incr(T, n);
        end = clock();
        cout << (end - start) / float(CLOCKS_PER_SEC) << endl;
    }
    delete [] T;
    return 0;
}

int main_algo(int argc, char * argv []) {

    if (argc < 3) {
        cout << "Usage : <nb_elem> <elem_1> ... <elem_n>" << endl;
        return 1;
    }

    ostringstream osstr;
    for (int i(1); i < argc; ++i) {
        osstr << argv[i] << " ";
    }
    istringstream isstr (osstr.str());

    unsigned n;
    isstr >> n;
    int T[n];
    for (unsigned i(0); i < n; ++i) {
        isstr >> T[i];
    }

    int res;
    /* */ res = algo::algo_naif(T, n);       /* */
    cout << res << endl;
    /* */ res = algo::algo_moins_naif(T, n); /* */
    cout << res << endl;
    /* */ res = algo::algo_div(T, n);        /* */
    cout << res << endl;
    /* */ res = algo::algo_incr(T, n);       /* */

    cout << res << endl;

    return 0;
}

int main (int argc, char * argv []) {
    int r;
    /* */ r = main_algo(argc, argv); /* */
    /* * / r = test_asymptote();      /* */
    return r;
}

