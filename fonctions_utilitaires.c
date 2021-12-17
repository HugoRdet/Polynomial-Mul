#include "fonctions_utilitaires.h"
#include <stdlib.h>
#include <stdio.h>




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

void mult_tab_constant_double(double C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]= ( (u_int32_t) (tab[i]*C ) ) % mod;
	}
}



void mult_tab_constant(int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]=multi_n_c(C,tab[i]);
	}
}

void add_mult_tab_constant(int32_t C,u_int32_t *tab,u_int64_t taille,u_int32_t *dest){
	for (u_int64_t i=0;i<taille;i++){
		dest[i]=add_n(dest[i], multi_n_c(C,tab[i])); 
	}
}


u_int32_t extendedEuclid(int b){
	int n0=mod;
	int b0=b %mod;
	int t0=0;
	int t=1;
	int q=(uint32_t) ((1.0*n0)/b0);
	int r=(((n0-q*b0)%mod)+mod)%mod;
	while (r>0) {
		int tmp=(((t0-q*t)%mod)+mod)%mod;
	
		t0=t;
		t=tmp;
		n0=b0;
		b0=r;
		q=(uint32_t) (((double)n0)/b0);
		r=(((n0-q*b0)%mod)+mod)%mod;
		
	}
	return (u_int32_t) t;
}



u_int32_t* genere_polynome(u_int64_t d){
	u_int32_t *res=(u_int32_t * ) malloc(sizeof(u_int32_t)*d);
	for (u_int64_t i=0;i<d;i++){
		res[i]=(u_int32_t) (rand() %10);
		
	}
	return res;
}

