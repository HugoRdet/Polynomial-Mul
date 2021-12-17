#include "test.h"



int main(int argc,char **argv){
    
    int choix=atoi(argv[1]);
  if (choix==1){
    int max=atoi(argv[2]);
    int pas=atoi(argv[3]);
    int essais=atoi(argv[4]);
    test_algos(max,pas,essais);
    return 0;
  }
  
  if (choix==2){
    int max=atoi(argv[2]);
    int essais=atoi(argv[3]);
    test_algos_TCK(max,essais);
  }
  
  
    /*
    u_int32_t *a=(u_int32_t *) malloc(sizeof(u_int32_t)*10);
    u_int32_t *b=(u_int32_t *) malloc(sizeof(u_int32_t)*10);
    
    a[0]=3653;	b[0]=5310;
    a[1]=4855;	b[1]=7438;
    a[2]=3232;	b[2]=2346;
    a[3]=1903;	b[3]=3364;
    a[4]=1549;	b[4]=7052;
    a[5]=928; 	b[5]=7521;
    a[6]=5579;	b[6]=7608;
    a[7]=5135;	b[7]=776;
    a[8]=920;	  b[8]=5176;
    a[9]=6888;	b[9]=7509;
  
    
  
    u_int32_t *res_TC=NULL;
    u_int32_t *res_karat=NULL;
    u_int64_t taille_res=0;
    mult_TC4(a,9,b,9,&res_TC,&taille_res);
    mult_poly_karasuba(a,9,b,9,&res_karat,&taille_res);
  
    printf("taille : %llu\n",taille_res);
    
    for (int i=0;i<taille_res;i++){
          
          printf("%d %d\n",res_karat[i],res_TC[i]);
    }
  
        
  
    free(a);
    free(b);
    free(res_karat);
    free(res_TC);
    */
  return 0;
}


