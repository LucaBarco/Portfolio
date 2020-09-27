//
// Created by Luca Barco on 13/01/2018.
//

#include "Item.h"
#include <stdlib.h>
#include <string.h>

Item NewItem(char *id,int n){
    Item x=malloc(sizeof(*x));
    strcpy(x->id,id);
    x->stazioni=calloc(n,sizeof(int));
    x->minuti=0;
    x->attivo=0;
    return x;
}
int ItemSearchStation(Item x,int id_stazione,int time){
    int i,minuti;
    if(x->attivo==0){
        x->stazioni[id_stazione]++;
        x->minuti=time;
        x->attivo=1;
        return 0;
    }
    else{
        minuti = time - x->minuti;
        x->minuti = 0;
        x->attivo=0;
        return minuti;
    }
    /*if(x->stazioni[id_stazione]>0 && x->time[id_stazione] != 0) {
            minuti = time - x->time[id_stazione];
            x->time[id_stazione] = 0;
            return minuti;
    }
    else{
            x->stazioni[id_stazione]++;
            x->time[id_stazione]=time;
            return 0;
        }*/
}
Item ItemSetVoid(){
    Item n=malloc(sizeof(*n));
    strcpy(n->id,"\0");
    n->minuti=0;
    n->stazioni=NULL;
    return n;
}
int ItemLess(Item a,Item b){
    if(strcmp(a->id,b->id)<0){
        return 1;
    }
    return 0;
}
int ItemEq(Item a,Item b){
    if(strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}
int ItemTipoOperazione(Item x){
    if(x->attivo!=0){
        return 1;
    }
    return 0;
}