//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E04_ESARRAY_H
#define E04_ESARRAY_H
#include "es.h"
#include <stdlib.h>
typedef struct tabEser_s *tabEser;

tabEser nuovaTabEs();
tabEser leggiFile_es(tabEser esercizi);
p_esercizio ricercaEser(tabEser esercizi,char *k);
void stampaEser(tabEser esercizi,char *k);
int contaEser(tabEser esercizi);
char *nomeGetEser(tabEser esercizi,int k);
void stampaTuttiEser(tabEser esercizi);

//inserire funzione che restituisce numero esercizi
//funzioni che permettano di accedere ai dettagli interni

#endif //E04_ESARRAY_H
