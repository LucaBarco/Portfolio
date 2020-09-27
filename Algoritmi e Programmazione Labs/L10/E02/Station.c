//
// Created by Luca Barco on 13/01/2018.
//

#include "Station.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 10
struct casella_s{
    char id[MAX];
    int posti;
    int bici;
};
casella readStation(char *id,int bici,int posti){
    casella new=malloc(sizeof(*new));
    strcpy(new->id,id);
    new->posti=posti;
    new->bici=bici;
    return new;
}
casella NewStation(casella x,casella y){
    strcpy(x->id,y->id);
    x->bici=y->bici;
    x->posti=y->posti;
    return x;
}
casella voidStation(){
    casella new=malloc(sizeof(*new));
    strcpy(new->id,"\0");
    new->bici=0;
    new->posti=0;
    return new;
}
int EqStation(casella a,casella b){
    return(strcmp(a->id,b->id));
}
char *GetId(casella x){
    return x->id;
}
int GetPosti(casella x){
    return x->posti;
}
int GetBici(casella x){
    return x->bici;
}
void PrintStation(casella x){
    printf("ID:%s BICI:%d POSTI:%d\n",x->id,x->bici,x->posti);
}
void diminuisciPosti(casella x){
    x->posti=x->posti-1;
}
void diminuisciBici(casella x){
    x->bici=x->bici-1;
}
void aumentaPosti(casella x){
    x->posti=x->posti+1;
}
void aumentaBici(casella x){
    x->bici=x->bici+1;
}