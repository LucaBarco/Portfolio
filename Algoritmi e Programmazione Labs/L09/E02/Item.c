//
// Created by Luca Barco on 20/12/2017.
//

#include "Item.h"
#include <stdlib.h>
#include <string.h>
struct Item_s{
    char *nome;
    int punti;
};
//itemsetvoid
Item ItemSetVoid(){
    Item x=malloc(sizeof(*x));
    x->nome=malloc(sizeof(char));
    strcpy(x->nome,"\0");
    x->punti=1500;
    return x;
}


//funzione lettura
Item ItemScan(FILE *fp){
    Item x=malloc(sizeof(*x));
    char nome[20];
    if(fp!=stdin) {
        if (fscanf(fp, "%s %d\n", nome, &x->punti) != EOF) {
            x->nome = strdup(nome);
            return x;
        }
        return ItemSetVoid();
    }
    else{
        printf("Inserisci il nome del nuovo giocatore: ");
        scanf("%s",nome);
        x->nome=strdup(nome);
        x->punti=10;
        return x;
    }
}

//funzione stampa
void ItemShow(FILE *fp,Item i){
    fprintf(fp,"Giocatore:%s \tPunti:%d\n",i->nome,i->punti);
    return;
}

//funzioni di confronto
int ItemGreater(Item a,Item b){
    if(a->punti>b->punti){
        return 1;
    }
    return 0;
}
int ItemLess(Item a,Item b){
    if(a->punti<b->punti){
        return 1;
    }
    return 0;
}
int ItemEq(Item a,Item b){
    if(strcmp(a->nome,b->nome)==0 && a->punti==b->punti){
        return 1;
    }
    return 0;
}
//accesso ai campi
char *ItemKeyGet(Item a){
    return a->nome;
}
int ItemGetPunti(Item a){
    return a->punti;
}
//aggiorna punti
void aggiornaPunti(Item gioc1,Item gioc2,int id_winner){
    if(id_winner==1){
        gioc1->punti=gioc1->punti+(gioc2->punti*0.25);
        gioc2->punti=(gioc2->punti)*0.75;
    }
    if(id_winner==2){
        gioc2->punti=gioc2->punti+(gioc1->punti*0.25);
        gioc1->punti=(gioc1->punti)*0.75;
    }
}