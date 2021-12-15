#ifndef __ALGORITHMES_H__
#define __ALGORITHMES_H__

#include "fonctions_utilitaires.h"

u_int32_t *mult_poly_naif(u_int32_t *res,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille);

void mult_poly_karasuba(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res );

void mult_TC3(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res );

void mult_TC4(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res );


#endif