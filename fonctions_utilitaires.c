#include "fonctions_utilitaires.h"
#include <stdlib.h>
#include <stdio.h>

u_int32_t mult_test( u_int32_t a, u_int32_t b){
	return (u_int32_t) ((( (u_int64_t) a ) * b ) % mod );
}

void mult_tab_constant_double(double C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]= ( (u_int32_t) (tab[i]*C ) ) % mod;
	}
}

void mult_tab_constant(u_int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]=multi_n(C,tab[i]);
	}
}

void add_mult_tab_constant(u_int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]+=multi_n(C,tab[i]);
	}
}

void add_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille){
	
	for( u_int64_t i=0;i<taille;i++){
		tab_res[i]=add_n(tab1[i],tab2[i]);
	}
	
}

void sous_tab(u_int32_t *tab_res ,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille){
	
	for( u_int64_t i=0;i<taille;i++){
		tab_res[i]=sous_n(tab1[i],tab2[i]);
	}
}

u_int32_t *mult_poly_naif(u_int32_t *res,u_int32_t *tab1,u_int32_t *tab2,u_int64_t taille){
	
	
	for (u_int64_t i=0;i<taille;i++){
		for (u_int64_t j=0;j<taille;j++){
			res[i+j]+=multi_n(tab1[i], tab2[j]);
		}
	}
	
	return res;
}




void karasuba_mult_poly_rec(u_int32_t *res,u_int32_t *A,u_int32_t *B,u_int64_t taille){
	
	if (taille<=N){
		mult_poly_naif(res,A,B,taille);
		return;
	}
	
	u_int64_t p=(taille>>1); //division par 2 (tronqué)
	
	
	u_int32_t *R0=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	karasuba_mult_poly_rec(R0,A,B,p);
	
	u_int32_t *R1=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	karasuba_mult_poly_rec(R1,A+p,B+p,p);
	
	
	
	u_int32_t *T0=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	add_tab(T0,A,A+p,p);
	
	
	u_int32_t *T1=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	add_tab(T1,B,B+p,p);
	
	
	u_int32_t *R2=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	karasuba_mult_poly_rec(R2,T0,T1,p);
	
	for (u_int64_t i=0;i<taille;i++){
		R2[i]=R2[i]-R1[i]-R0[i];
	}
	
	for (u_int64_t i=0;i<taille;i++){
		res[2*p+i]+=R1[i];
		res[p+i]+=R2[i];
		res[i]+=R0[i];
	}
	
	free(R0);
	free(R1);
	free(R2);
	
	free(T1);
	free(T0);
}


void karasuba_mult_poly_rec_ameliore(u_int32_t *res,u_int32_t *A,u_int32_t *B,u_int64_t taille){
	
	if (taille<=N){
		mult_poly_naif(res,A,B,taille);
		return;
	}
	
	u_int64_t p=(taille>>1); //division par 2 (tronqué)
	
	karasuba_mult_poly_rec_ameliore(res,A,B,p);
	karasuba_mult_poly_rec_ameliore(res+taille,A+p,B+p,p);
	
	u_int32_t *R2=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	u_int32_t *R3=(u_int32_t *) calloc(taille,sizeof(u_int32_t));
	
	
	
	add_tab(R3,A,A+p,p);
	add_tab(R3+p,B,B+p,p);
	
	
	karasuba_mult_poly_rec_ameliore(R2,R3,R3+p,p);
	
	for (u_int64_t i=0;i<taille;i++){
		R2[i]=R2[i]-(res+taille)[i]-res[i];
	}
	
	for (u_int64_t i=0;i<taille;i++){
		res[p+i]+=R2[i];
	}
	
	free(R2);
	free(R3);
	
}



void mult_poly_karasuba(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res ){
	u_int64_t tmp_taille=1;
	u_int64_t cpt=0;
	u_int64_t max_taille=max(taille_a,taille_b);
	
	while (max_taille>tmp_taille) {
		tmp_taille*=2;
	}
	
	u_int32_t *res_tab=(u_int32_t *) calloc(tmp_taille*2,sizeof(u_int32_t));
	
	u_int32_t *tmp_a=(u_int32_t *) malloc(sizeof(u_int32_t)*tmp_taille);
	u_int32_t *tmp_b=(u_int32_t *) malloc(sizeof(u_int32_t)*tmp_taille);
	
	for (u_int64_t i=0;i<taille_a;i++){
		tmp_a[i]=a[i];
	}
	
	for (u_int64_t i=taille_a; i<tmp_taille; i++) {
		tmp_a[i]=0;
	}
	for (u_int64_t i=0;i<taille_b;i++){
		tmp_b[i]=b[i];
	}
	for (u_int64_t i=taille_b; i<tmp_taille; i++) {
		tmp_a[i]=0;
	}
	
	karasuba_mult_poly_rec_ameliore(res_tab,tmp_a,tmp_b,tmp_taille);
	
	free(tmp_a);
	free(tmp_b);
	
	
	*res=(u_int32_t*) realloc(res_tab, sizeof(u_int32_t)*(taille_a+taille_b-1));;
	*taille_res=(taille_a+taille_b-1);
	
}

void mult_poly_TC3(u_int32_t *res,u_int32_t *A,u_int32_t *B,u_int64_t taille){
	
	if (taille<=N){
		mult_poly_naif(res,A,B,taille);
		return;
	}
	
	
	u_int64_t k=(u_int32_t) (taille/3.0);
	
	u_int32_t *a_0=A;
	u_int32_t *a_1=A+k;
	u_int32_t *a_2=A+2*k;
	
	u_int32_t *b_0=B;
	u_int32_t *b_1=B+k;
	u_int32_t *b_2=B+2*k;
	
	
// pour tc3 -> 5x5 
//	0	1	2	3	4	
//
//	1	0	0	0	0	
//	1	1	1	1	1	
//	1	2	4	8	16	
//	1	3	9	27	81	
//	1	4	16	64	256	

	
	u_int32_t *arg_a=(u_int32_t *) malloc(sizeof(u_int32_t)*k);
	u_int32_t *arg_b=(u_int32_t *) malloc(sizeof(u_int32_t)*k);
	
	
	
	//valuation en 0
	u_int32_t *v_0=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	mult_poly_TC3(v_0,a_0,b_0,k);
	
	//valuation en 1
	u_int32_t *v_1=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	
	add_tab(arg_a,a_0,a_1,k);
	add_tab(arg_a,arg_a,a_2,k);
	
	add_tab(arg_b,b_0,b_1,k);
	add_tab(arg_b,arg_b,b_2,k);
	
	mult_poly_TC3(v_1,arg_a,arg_b,k);
	
	
	
	
	//valuation en 2
	u_int32_t *v_2=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	
	mult_tab_constant(2,a_1,k,arg_a);
	add_tab(arg_a,arg_a,a_0,k);
	add_mult_tab_constant(4,a_2,k,arg_a);
	
	mult_tab_constant(2,b_1,k,arg_b);
	add_tab(arg_b,arg_b,b_0,k);
	add_mult_tab_constant(4,b_2,k,arg_b);
	
	mult_poly_TC3(v_2,arg_a,arg_b,k);
	
	
	
	//valuation en 3
	u_int32_t *v_3=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	
	mult_tab_constant(3,a_1,k,arg_a);
	add_tab(arg_a,arg_a,a_0,k);
	add_mult_tab_constant(9,a_2,k,arg_a);
	
	mult_tab_constant(3,b_1,k,arg_b);
	add_tab(arg_b,arg_b,b_0,k);
	add_mult_tab_constant(9,b_2,k,arg_b);
	
	mult_poly_TC3(v_3,arg_a,arg_b,k);
	
	
	
	//valuation en 4
	u_int32_t *v_4=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	
	mult_tab_constant(4,a_1,k,arg_a);
	add_tab(arg_a,arg_a,a_0,k);
	add_mult_tab_constant(16,a_2,k,arg_a);
	
	mult_tab_constant(4,b_1,k,arg_b);
	add_tab(arg_b,arg_b,b_0,k);
	add_mult_tab_constant(16,b_2,k,arg_b);
	
	mult_poly_TC3(v_4,arg_a,arg_b,k);
	
	free(arg_b);
	free(arg_a);
	
// pour tc3 -> 5x5 
//	0	1	2	3	4
//
//	1	0	0	0	0
//	1	1	1	1	1
//	1	2	4	8	16
//	1	3	9	27	81
//	1	4	16	64	256

//inverse:
//det 1/24

//	24 |   0 |   0 |  0 |  0
//	-50|  96 | -72 | 32 | -6
//	35 |-104 | 114 |-56 | 11
//	-10|  36 | -48 | 28 | -6
//	 1 |  -4 |   6 | -4 |  1
	
	u_int64_t decalage=k;
	
	u_int32_t *c0=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	u_int32_t *c1=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	u_int32_t *c2=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	u_int32_t *c3=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	u_int32_t *c4=(u_int32_t *) malloc(sizeof(u_int32_t)*(2*k));
	
	//c0
	mult_tab_constant(24,v_0,2*k,c0);
	
	
	
	//c1
	mult_tab_constant(mod-50,v_0,2*k,c1);
	//printf("je suis ici:%d %d\n",c1[0],c1[1]);
	add_mult_tab_constant(96,v_1,2*k,c1);
	add_mult_tab_constant(mod-72,v_2,2*k,c1);
	add_mult_tab_constant(32,v_3,2*k,c1);
	add_mult_tab_constant(mod-6,v_4,2*k,c1);
	
	//c2
	mult_tab_constant(35,v_0,2*k,c2);
	add_mult_tab_constant(mod-104,v_1,2*k,c2);
	add_mult_tab_constant(114,v_2,2*k,c2);
	add_mult_tab_constant(mod-56,v_3,2*k,c2);
	add_mult_tab_constant(11,v_4,2*k,c2);
	
	//c3
	mult_tab_constant(mod-10,v_0,2*k,c3);
	add_mult_tab_constant(36,v_1,2*k,c3);
	add_mult_tab_constant(mod-48,v_2,2*k,c3);
	add_mult_tab_constant(28,v_3,2*k,c3);
	add_mult_tab_constant(mod-6,v_4,2*k,c3);
	
	
	//c4
	mult_tab_constant(1,v_0,2*k,c4);
	add_mult_tab_constant(mod-4,v_1,2*k,c4);
	add_mult_tab_constant(6,v_2,2*k,c4);
	add_mult_tab_constant(mod-4,v_3,2*k,c4);
	add_mult_tab_constant(1,v_4,2*k,c4);
	
	
	
	add_tab(res,res,c0,2*k);
	add_tab(res+k,res+k,c1,2*k);
	add_tab(res+2*k,res+2*k,c2,2*k);
	add_tab(res+3*k,res+3*k,c3,2*k);
	add_tab(res+4*k,res+4*k,c4,2*k);
	
	
	mult_tab_constant_double(1/24.0,res,taille*2,res);
	
	free(v_0);
	free(v_1);
	free(v_2);
	free(v_3);
	free(v_4);
	free(c0);
	free(c1);
	free(c2);
	free(c3);
	free(c4);
}

void mult_poly_TC(u_int32_t *a,u_int64_t taille_a,u_int32_t *b,u_int64_t taille_b,u_int32_t **res,u_int64_t *taille_res ){
	u_int64_t tmp_taille=1;
	u_int64_t cpt=0;
	u_int64_t max_taille=max(taille_a,taille_b);
	
	while (max_taille>tmp_taille) {
		tmp_taille*=3;
	}
	
	u_int32_t *res_tab=(u_int32_t *) calloc(tmp_taille*2,sizeof(u_int32_t));
	
	u_int32_t *tmp_a=(u_int32_t *) malloc(sizeof(u_int32_t)*tmp_taille);
	u_int32_t *tmp_b=(u_int32_t *) malloc(sizeof(u_int32_t)*tmp_taille);
	
	for (u_int64_t i=0;i<taille_a;i++){
		tmp_a[i]=a[i];
	}
	
	for (u_int64_t i=taille_a; i<tmp_taille; i++) {
		tmp_a[i]=0;
	}
	for (u_int64_t i=0;i<taille_b;i++){
		tmp_b[i]=b[i];
	}
	for (u_int64_t i=taille_b; i<tmp_taille; i++) {
		tmp_a[i]=0;
	}
	
	
	mult_poly_TC3(res_tab,tmp_a,tmp_b,tmp_taille);
	
	free(tmp_a);
	free(tmp_b);
	
	
	
	*res=(u_int32_t*) realloc(res_tab, sizeof(u_int32_t)*(taille_a+taille_b-1));;
	*taille_res=(taille_a+taille_b-1);
	
}


		