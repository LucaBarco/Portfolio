//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E04_ES_H
#define E04_ES_H
#define MAXN 51
#include <stdio.h>

typedef struct esercizio_s{
    char nome[MAXN];
    char categoria[MAXN];
    char tipologia[MAXN];
}esercizio, *p_esercizio;

esercizio eserScan(FILE *fp);
int eserEq(esercizio a,esercizio b);
esercizio eserVoid();
#endif //E04_ES_H
