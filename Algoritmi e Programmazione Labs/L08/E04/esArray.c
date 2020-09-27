//
// Created by Luca Barco on 10/12/2017.
//

#include "esArray.h"
#include <string.h>
struct tabEser_s{
    p_esercizio ElencoEsercizi;
    int n_esercizi;
};

tabEser nuovaTabEs(){
    tabEser a=malloc(sizeof(*a));
    return a;
}
tabEser leggiFile_es(tabEser esercizi){
    FILE *fp=fopen("esercizi.txt","r");
    int i=0,N;
    esercizio temp;
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&N);
    esercizi->n_esercizi=N;
    esercizi->ElencoEsercizi=(p_esercizio)malloc(esercizi->n_esercizi*sizeof(esercizio));
    while(eserEq((temp=eserScan(fp)),eserVoid())!=1 && i<esercizi->n_esercizi){
        strcpy(esercizi->ElencoEsercizi[i].nome,temp.nome);
        strcpy(esercizi->ElencoEsercizi[i].tipologia,temp.tipologia);
        strcpy(esercizi->ElencoEsercizi[i].categoria,temp.categoria);
        i++;
    }
    fclose(fp);
    return esercizi;
}



p_esercizio ricercaEser(tabEser esercizi,char *k){
    int i;
    for(i=0;i<esercizi->n_esercizi;i++){
        if(strcmp(esercizi->ElencoEsercizi[i].nome,k)==0){
            return &(esercizi->ElencoEsercizi[i]);
        }
    }
    return NULL;
}
void stampaEser(tabEser esercizi,char *k){
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

int contaEser(tabEser esercizi){
    return esercizi->n_esercizi;
}

char *nomeGetEser(tabEser esercizi,int k){
    return esercizi->ElencoEsercizi[k].nome;
}


void stampaTuttiEser(tabEser esercizi){
    int k;
    for(k=0;k<esercizi->n_esercizi;k++){
        printf("%s\n",esercizi->ElencoEsercizi[k].nome);
    }
}