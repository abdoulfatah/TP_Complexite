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

using namespace std;

namespace {

    int algo_moins_naif(int * T, unsigned n);
    int algo_div(int * T, unsigned n);
    int algo_div_impl(int * T, int k, int l);

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

    int algo_div(int * T, unsigned n) {
        return algo_div_impl(T, 0, n);
    }

    int algo_div_impl(int * T, int k, int l) {
        int sz = l - k;
        if (sz == 1) {
            return T[k];
        }
        else if (sz == 2) {
            return max(max(T[k], T[k+1]), T[k] + T[k+1]);
        }

        int sum_0, sum_1, sum_2, sum_3, sum_4, sum_tmp;
        int j = sz / 2;

        sum_1 = algo_div_impl(T, k, k+j);
        sum_2 = algo_div_impl(T, k+j+1, l);

        // sous-sequence terminant par le pivot (T[j])
        sum_3 = sum_tmp = T[j];
        for (int i(j-1); i >= k; --i) {
            sum_tmp = sum_tmp + T[i];
            if (sum_tmp > sum_3)
                sum_3 = sum_tmp;
        }

        // sous-sequence debutant par le pivot (T[j])
        sum_4 = sum_tmp = T[j];
        for (int i(j+1); i < l; ++i) {
            sum_tmp = sum_tmp + T[i];
            if (sum_tmp > sum_4)
                sum_4 = sum_tmp;
        }

        sum_0 = sum_3 + sum_4 - T[j];

        return max(max(sum_0, sum_1), sum_2);

    }

}

int main (int argc, char * argv []) {

    if (argc < 3) {
        cout << "Usage : <nb_elem> <elem_1> ... <elem_n>" << endl;
        return 1;
    }

    ostringstream osstr;
    for (unsigned i(1); i < argc; ++i) {
        osstr << argv[i] << " ";
    }
    istringstream isstr (osstr.str());

    int n;
    isstr >> n;
    int T[n];
    for (unsigned i(0); i < n; ++i) {
        isstr >> T[i];
    }

    int res;
    /* * / res = algo_moins_naif(T, n); /* */
    /* */ res = algo_div(T, n);     /* */

    cout << res << endl;

    return 0;
}
