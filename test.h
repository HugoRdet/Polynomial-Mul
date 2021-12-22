#ifndef __TESTS_H__
#define __TESTS_H__

#include "algorithmes.h"

void test_TC(u_int64_t d,u_int64_t pas,int nb_essais);
void test_algos(u_int64_t d,u_int64_t pas,int nb_essais);
void test_algos_TCK(u_int64_t d,int nb_essais);
void test_algos_2(u_int64_t d,u_int64_t pas,int nb_essais);
void test_algo_naif(u_int64_t d,u_int64_t pas,int nb_essais);
void test_algo(u_int64_t d,u_int64_t pas,int nb_essais);
#endif