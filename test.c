#include "test.h"


void test_TC(u_int64_t d,u_int64_t pas,int nb_essais){
	FILE *f=fopen("tests/test_TC","w");
	srand(time(NULL));
	for (u_int64_t i=pas;i<d;i+=pas){
		double res_TC3=0.0;
		double res_TC4=0.0;
		
		
		for (u_int32_t n=0;n<nb_essais;n++){
			
			clock_t tmp_start;
			clock_t tmp_final;
			
			u_int32_t *tmp_a=genere_polynome(i);
			u_int32_t *tmp_b=genere_polynome(i);
			u_int32_t *res=NULL;
			u_int64_t taille_res=0;
			
			tmp_start = clock ();
			mult_TC3(tmp_a,i,tmp_b,i, &res, &taille_res);
			tmp_final = clock ();
			res_TC3+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			tmp_start = clock ();
			mult_TC4(tmp_a,i,tmp_b,i, &res, &taille_res);
			tmp_final = clock ();
			res_TC4+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			free(tmp_a);
			free(tmp_b);
			free(res);
			
		}
		res_TC3/=nb_essais;
		res_TC4/=nb_essais;
		printf("%lld %lf %lf\n",i,res_TC3,res_TC4);
		fprintf(f,"%lld %lf %lf\n",i,res_TC3,res_TC4);
	}
	
	fclose(f);
	
}

void test_algos(u_int64_t d,u_int64_t pas,int nb_essais){
	FILE *f=fopen("tests/test_general","w");
	srand(time(NULL));
	for (u_int64_t i=pas;i<d;i+=pas){
		double res_naif=0.0;
		double res_karat=0.0;
		double res_TC4=0.0;
		
		
		for (u_int32_t n=0;n<nb_essais;n++){
			
			clock_t tmp_start;
			clock_t tmp_final;
			
			u_int32_t *tmp_a=genere_polynome(i);
			u_int32_t *tmp_b=genere_polynome(i);
			u_int32_t *res_karat_tab=NULL;
			u_int32_t *res_TC_tab=NULL;
			u_int64_t taille_res=0;
			
			u_int32_t *res_naif_tab=(u_int32_t *) calloc(i*2,sizeof(u_int32_t));
			
			
			
			tmp_start = clock ();
			mult_poly_naif(res_naif_tab,tmp_a,tmp_b,i);
			tmp_final = clock ();
			res_naif+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			tmp_start = clock ();
			mult_poly_karasuba(tmp_a,i,tmp_b,i, &res_karat_tab, &taille_res);
			tmp_final = clock ();
			res_karat+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			
			
			tmp_start = clock ();
			mult_TC4(tmp_a,i,tmp_b,i, &res_TC_tab, &taille_res);
			tmp_final = clock ();
			res_TC4+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			
			
			for (u_int64_t j=0;j<i*2;j++){
				if (res_naif_tab[j]!=res_karat_tab[j]){
					
					printf("ERREUR VALIDITE 1\n");
					fclose(f);
					return;
				}
				
				if (res_naif_tab[j]!=res_TC_tab[j]){
					printf("J %lld\n",j);
					for (u_int64_t x=0;x<i*2;x++){
						printf("%llu %d\t%d\n",x,res_naif_tab[x],res_TC_tab[x]);
					}
					printf("ERREUR VALIDITE 2\n");
					fclose(f);
					return;
				}
				
				
			}
			
			free(tmp_a);
			free(tmp_b);
			free(res_karat_tab);
			free(res_TC_tab);
			free(res_naif_tab);
		}
		res_naif/=nb_essais;
		res_karat/=nb_essais;
		res_TC4/=nb_essais;
		printf("%lld %lf %lf %lf\n",i,res_naif,res_karat,res_TC4);
		fprintf(f,"%lld %lf %lf %lf\n",i,res_naif,res_karat,res_TC4);
	}
	
	fclose(f);
	
}

void test_algos_TCK(u_int64_t d,int nb_essais){
	FILE *f=fopen("tests/test_general_TCK","w");
	srand(time(NULL));
	u_int64_t cpt=1;
	for (u_int64_t i=1;i<d;i++){
		double res_naif=0.0;
		double res_karat=0.0;
		double res_TC4=0.0;
		cpt*=2;
		printf("ok ok ok\n");
		for (u_int32_t n=0;n<nb_essais;n++){
			
			clock_t tmp_start;
			clock_t tmp_final;
			
			u_int32_t *tmp_a=genere_polynome(cpt);
			u_int32_t *tmp_b=genere_polynome(cpt);
			u_int32_t *res_karat_tab=NULL;
			u_int32_t *res_TC_tab=NULL;
			u_int64_t taille_res=0;
			
			
		
			
			tmp_start = clock ();
			mult_poly_karasuba(tmp_a,cpt,tmp_b,cpt, &res_karat_tab, &taille_res);
			tmp_final = clock ();
			res_karat+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			
			
			tmp_start = clock ();
			mult_TC4(tmp_a,cpt,tmp_b,cpt, &res_TC_tab, &taille_res);
			tmp_final = clock ();
			res_TC4+=((double)(tmp_final - tmp_start)/CLOCKS_PER_SEC);
			
			
			
			free(tmp_a);
			free(tmp_b);
			free(res_karat_tab);
			free(res_TC_tab);
			
		}
		res_naif/=nb_essais;
		res_karat/=nb_essais;
		res_TC4/=nb_essais;
		printf("%lld %lf %lf\n",cpt,res_karat,res_TC4);
		fprintf(f,"%lld %lf %lf\n",cpt,res_karat,res_TC4);
	}
	
	fclose(f);
	
}
