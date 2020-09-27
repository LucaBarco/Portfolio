//
// Created by Luca Barco on 13/01/2018.
//

#include "ST.h"

#include <stdlib.h>
#include <string.h>
#ifndef MAX
#define MAX 10
#endif


struct symboltable{
    casella *tab;
    int n;
};

ST STinit(int n){
    int i;
    ST new=malloc(sizeof(*new));
    new->n=n;
    new->tab=malloc(n*sizeof(*new->tab));
    for(i=0;i<new->n;i++){
        new->tab[i]=voidStation();
    }
    return new;
}
void STinsert(ST st,casella x){
    int i;
    for(i=0;i<st->n;i++){
        if(EqStation(st->tab[i],voidStation())==0){
            st->tab[i]=NewStation(st->tab[i],x);
            return;
        }
    }
}
char* STretrieveID(ST st,int i){
    if(i>=0 && i<st->n) {
        return GetId(st->tab[i]);
    }
    else{
        return NULL;
    }
}
int STretrieveIndex(ST st,char *k){
    int i;
    for(i=0;i<st->n;i++){
        if(strcmp(k,GetId(st->tab[i]))==0){
            return i;
        }
    }
    return -1;
}
int STretrievePosti(ST st,int i){
    return GetPosti(st->tab[i]);
}
int STretrieveBici(ST st,int i){
    return GetBici(st->tab[i]);
}
int getSize(ST st){
    return st->n;
}
void STprint(ST st){
    int i;
    for(i=0;i<st->n;i++){
        PrintStation(st->tab[i]);
    }
}
void decreasePosti(ST st,int i){
    diminuisciPosti(st->tab[i]);
}
void decreaseBici(ST st,int i){
    diminuisciBici(st->tab[i]);
}
void increasePosti(ST st,int i){
    aumentaPosti(st->tab[i]);
}
void increaseBici(ST st,int i){
    aumentaBici(st->tab[i]);
}