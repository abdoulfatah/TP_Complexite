/*
 * @File sous-sequence_max.cxx
 *
 * @Author Sebastien Delecraz, Eloi Perdereau
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
                for (unsigned k(i+1); k <= j; ++k)
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
        bool maj(false);

        for (unsigned i(1); i < n; ++i) {
            sum_1 += T[i];
            sum_2 += T[i];
            if (T[i] < 0) {
                if ((T[i] > sum_max)) {
                    sum_max = T[i];
                    sum_1 = 0;
                    sum_2 = 0;
                }
                if (sum_2 < 0) sum_2 = 0;
            }
            else {
                int sum_tmp(sum_max);
                if (sum_1 + sum_tmp > sum_tmp) {
                    sum_max += sum_1;
                    maj = true;
                }
                if (sum_2 > sum_tmp && sum_2 > sum_1 + sum_tmp) {
                    sum_max = sum_2;
                    sum_1 = 0;
                    sum_2 = 0;
                    maj = true;
                }
                if (maj) {
                    sum_1 = 0;
                    sum_2 = 0;
                    maj = false;
                }
            }
        }
        return sum_max;
    }

}

void fill_with_random(int * T, unsigned k, unsigned l) {
    // fill T[i] to T[l-1] with random integers from -99 to 99
    // srand() must already have been called
    for (unsigned i(k); i < l; ++i) {
        int x = rand() % 100;
        T[i] = rand() % 2 ? -x : x;
    }
}

int test_algos(int argc, char * argv []) {
    unsigned n (10);
    unsigned failures (0);
    unsigned long iterations (100);
    bool verbose (false);
    srand(time(NULL));

    if (argc == 2) {
        istringstream isstr (argv[1]);
        isstr >> verbose;
    }

    cout << "Testing algorithms..." << '\n';
    for (unsigned i(0); i < iterations; ++i) {
        int * T = new int [n];
        fill_with_random(T, 0, n);
        int res_naif       = algo::algo_naif(T, n);
        int res_moins_naif = algo::algo_moins_naif(T, n);
        int res_div        = algo::algo_div(T, n);
        int res_incr       = algo::algo_incr(T, n);

        if (res_naif != res_moins_naif || res_naif != res_div       ||
            res_naif != res_incr       || res_moins_naif != res_div ||
            res_moins_naif != res_incr || res_div != res_incr) {
            ++failures;
            if (verbose) {
                cout << i << ":\t"
                     << res_naif << '\t' << res_moins_naif   << '\t'
                     << res_div  << '\t' << res_incr << endl << '\t';
                for (unsigned j(0); j < n; ++j) {
                    cout << T[j] << ' ';
                }
                cout << endl;
            }
        }
        delete [] T;
    }
    cout << "Total : "
         << failures << " failures over "
         << iterations << " iterations for a total of "
         << failures / double(iterations) * 100 << "\% failures" << endl;
    return 0;
}

int test_asymptote() {
    unsigned n_max = 1000000000;
    unsigned step = 10;
    clock_t start, end;
    int * T = new int [n_max];
    unsigned start_index = 0;
    srand(time(NULL));

    cout << "n;secondes" << endl;
    for (unsigned n(step);  n <= n_max; n+=step) {
        if (n >= 100         && n < 1000)         step = 10;
        if (n >= 1000        && n < 10000)        step = 100;
        if (n >= 10000       && n < 100000)       step = 1000;
        if (n >= 100000      && n < 1000000)      step = 10000;
        if (n >= 1000000     && n < 10000000)     step = 100000;
        if (n >= 10000000    && n < 100000000)    step = 1000000;
        if (n >= 100000000   && n < 1000000000)   step = 10000000;
  
  
        fill_with_random(T, start_index, n);
        start_index = n;

        cout << n << ";";
        start = clock();
        algo::algo_incr(T, n);
        end = clock();
        cout << (end - start) / float(CLOCKS_PER_SEC) << endl;
        if ((end - start) / float(CLOCKS_PER_SEC) > 5.0) break;
    }
    delete [] T;
    return 0;
}

int main_algo(int argc, char * argv []) {

    unsigned n;
    int * T;

    cin >> n;
    T = new int[n];
    for (unsigned i(0); i < n; ++i) {
        cin >> T[i];
    }

    int res;
    /* * / res = algo::algo_naif(T, n);       /* */
    /* * / res = algo::algo_moins_naif(T, n); /* */
    /* * / res = algo::algo_div(T, n);        /* */
    /* */ res = algo::algo_incr(T, n);       /* */

    cout << res << endl;

    delete [] T;

    return 0;
}

int main (int argc, char * argv []) {
    int r;
    /* * / r = main_algo(argc, argv);  /* */
    /* */ r = test_asymptote();       /* */
    /* * / r = test_algos(argc, argv); /* */
    return r;
}

