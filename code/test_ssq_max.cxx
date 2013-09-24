/*
 * @File preformances.cxx
 *
 * @Author eloi
 *
 * @Date 16-09-2013
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "sous-sequence_max.h"

using namespace std;

int main (int argc, char * argv[]) {

    unsigned n_max = 5000000;
    unsigned step = 1000;
    clock_t start, end;

    cout << "n;secondes" << endl;
    for (unsigned i(1); i <= n_max/step; ++i) {
        unsigned n = i * step;
        int T[n];

        // generate random array of n integers from -99 to 99
        for (unsigned j(0); j < n; ++j) {
            int sign = rand() % 2;
            int x = rand() % 100;
            T[j] = sign ? -x : x;
        }

        cout << n << ";";
        start = clock();
        int res_incr = algo::algo_incr(T, n);
        end = clock();
        cout << (end - start) / float(CLOCKS_PER_SEC) << endl;
        int res_juste = algo::algo_moins_naif(T, n);
        if (res_juste != res_incr) {
            cout << "faux : " << res_incr << ' ' << res_juste << endl;
        }
    }

    return 0;

}
