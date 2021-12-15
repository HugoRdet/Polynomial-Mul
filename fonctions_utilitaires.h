#ifndef __FONCTIONS_UTILITAIRES_H__
#define __FONCTIONS_UTILITAIRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define N 0x0100000000
#define N 1
#define mod 7789
#define add_n(a,b)    ((u_int32_t) ((( (u_int64_t) ((a)%mod)+mod ) + (((b)%mod)+mod)) % mod ) )
#define sous_n(a,b)   ((u_int32_t) (((( (u_int64_t) ((a)%mod)+mod ) - (((b)%mod)+mod)) +mod) % mod ) )
#define multi_n(a,b)  ((u_int32_t) ((( (u_int64_t) ((a)%mod)+mod ) * (((b)%mod)+mod)) % mod ) )
#define multi_n_c(a,b)  ((u_int32_t) ((( (u_int64_t) ((a)%mod)+mod ) * (((b)%mod)+mod)) % mod ) )

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

void add_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);
void sous_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);
u_int32_t extendedEuclid(int b);

void mult_tab_constant_double(double C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest);
void mult_tab_constant(int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest);
void add_mult_tab_constant(int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest);

u_int32_t extendedEuclid(int b);


#endif