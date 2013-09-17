/*
 * @File sous-sequence_max.h
 *
 * @Author eloi
 *
 * @Date 16-09-2013
 *
 */
#ifndef __SOUS_SEQUENCE_MAX_H__
#define __SOUS_SEQUENCE_MAX_H__

namespace algo {
    int algo_naif(int * T, unsigned n);
    int algo_div(int * T, unsigned n);
    int algo_div_impl(int k, int l);
    int algo_incr(int * T, unsigned n);
}

#endif /* __SOUS_SEQUENCE_MAX_H__ */
