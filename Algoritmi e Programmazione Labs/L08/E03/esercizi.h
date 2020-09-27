//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E03_ESERCIZI_H
#define E03_ESERCIZI_H

#define MAXN 51
typedef struct esercizio_s{
    char nome[MAXN];
    char categoria[MAXN];
    char tipologia[MAXN];
}esercizio, *p_esercizio;

typedef struct tabEser_s{
    p_esercizio ElencoEsercizi;
    int n_esercizi;
}tabEser;

p_esercizio leggiFile_es(tabEser *esercizi);
p_esercizio ricercaEser(tabEser *esercizi,char *k);
void stampaEser(tabEser *esercizi,char *k);

#endif //E03_ESERCIZI_H
