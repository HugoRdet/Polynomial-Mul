#ifndef __FICHIER_H__
#define __FICHIER_H__

#include "graphe_utilitaires.h"
#include "algos_graphes.h"

graphe *importer_graphe(char *fichier);
void test_algos_2(int taille_max,int pas,int NB_TESTS);
void test_algos_3(int taille_max,int pas,int NB_TESTS);
#endif
