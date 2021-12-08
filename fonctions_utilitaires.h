#ifndef __FONCTIONS_UTILITAIRES_H__
#define __FONCTIONS_UTILITAIRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define N 0x0100000000
#define N 1
#define mod 100000

#define add_n(a,b)    ((u_int32_t) ((( (u_int64_t) a ) +b ) % mod ) )
#define sous_n(a,b)   ((u_int32_t) ((( (u_int64_t) a ) -b ) % mod ) )
#define multi_n(a,b)  ((u_int32_t) ((( (u_int64_t) a ) * b) % mod ) )

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

void add_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);
void sous_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);

u_int32_t *mult_poly_naif(u_int32_t *res,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);

void mult_poly_karasuba(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res );

void mult_poly_TC(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res );


#endif