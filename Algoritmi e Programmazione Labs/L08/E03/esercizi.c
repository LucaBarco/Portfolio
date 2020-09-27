//
// Created by Luca Barco on 10/12/2017.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esercizi.h"

p_esercizio leggiFile_es(tabEser *esercizi){
    FILE *fp=fopen("esercizi.txt","r");
    int i=0;
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&(esercizi->n_esercizi));
    esercizi->ElencoEsercizi=(p_esercizio)malloc(esercizi->n_esercizi*sizeof(esercizio));
    while(fscanf(fp,"%s %s %s\n",esercizi->ElencoEsercizi[i].nome,esercizi->ElencoEsercizi[i].categoria,esercizi->ElencoEsercizi[i].tipologia)!=EOF && i<esercizi->n_esercizi){
        i++;
    }
    fclose(fp);
    return esercizi->ElencoEsercizi;
}
p_esercizio ricercaEser(tabEser *esercizi,char *k){
    int i;
    for(i=0;i<esercizi->n_esercizi;i++){
        if(strcmp(esercizi->ElencoEsercizi[i].nome,k)==0){
            return &(esercizi->ElencoEsercizi[i]);
        }
    }
    return NULL;

}
void stampaEser(tabEser *esercizi,char *k){
    p_esercizio i;
    i=ricercaEser(esercizi,k);
  if(i!=NULL){
      printf("---------------Esercizio Trovato!---------------\n");
      printf("Esercizio:\n\tNome:%s \tCategoria:%s \tTipologia:%s\n",i->nome,i->categoria,i->tipologia);
  }
    else{
      printf("----------Nessun esercizio trovato con questa chiave!----------\n");
  }
    return;
}
