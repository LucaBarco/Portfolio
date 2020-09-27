//
// Created by Luca Barco on 20/12/2017.
//

#ifndef E02_ITEM_H
#define E02_ITEM_H
#include <stdio.h>
typedef struct Item_s *Item;
//itemsetvoid
Item ItemSetVoid();

//funzione lettura
Item ItemScan(FILE *fp);

//funzione stampa
void ItemShow(FILE *fp,Item i);

//funzioni di confronto
int ItemGreater(Item a,Item b);
int ItemLess(Item a,Item b);
int ItemEq(Item a,Item b);

//accesso ai campi
char *ItemKeyGet(Item a);
int ItemGetPunti(Item a);

//aggiornamenti punti
void aggiornaPunti(Item gioc1,Item gioc2,int id_winner);

#endif //E02_ITEM_H
