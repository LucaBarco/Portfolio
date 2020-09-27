//
// Created by Luca Barco on 13/01/2018.
//

#ifndef E02_ITEM_H
#define E02_ITEM_H
#include <stdio.h>
#define MAX 10

typedef struct item{
    char id[MAX];
    int *stazioni;
    int attivo;
    int minuti;
}*Item;
typedef char* Key;

Item NewItem(char *id,int n);
int ItemSearchStation(Item x,int id_stazione,int time);
Item ItemSetVoid();
int ItemLess(Item a,Item b);
int ItemEq(Item a,Item b);
int ItemTipoOperazione(Item x); //1 se parcheggio, 0 se avvio noleggio

#endif //E02_ITEM_H
