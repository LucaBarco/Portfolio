//
// Created by Luca Barco on 19/12/2017.
//

#ifndef E01_ITEM_H
#define E01_ITEM_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Item_s{
    char *key;
    int N;

}Item;

//funzione estrazione della chiave
char *KEYget(Item i);

//ItemScan
Item ITEMscan(FILE *fp,int *dx,int *sx);

//ITEMprint
void ITEMprint(FILE *fp,Item x);

//ITEMequal
int ITEMequal(Item a,Item b);

//funzione itemsetvoid
Item ITEMsetVoid();
#endif //E01_ITEM_H
