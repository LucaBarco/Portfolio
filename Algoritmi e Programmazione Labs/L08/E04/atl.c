//
// Created by Luca Barco on 10/12/2017.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atl.h"
#define MAXC 26
atleta atletaScan(FILE *fp) {
    char nome[MAXC], cognome[MAXC], categoria[MAXC], codice[6], data[11];
    atleta temp;
    if (fscanf(fp, "%s %s %s %s %s %d\n", codice, cognome, nome, categoria, data, &temp.ore) != EOF) {

        temp.codice=malloc(6*sizeof(char));
        strcpy(temp.codice,codice);

        temp.n_cognome=strlen(cognome);
        temp.cognome=malloc(temp.n_cognome*sizeof(char));
        strcpy(temp.cognome,cognome);

        temp.n_nome=strlen(nome);
        temp.nome=malloc(temp.n_nome*sizeof(char));
        strcpy(temp.nome,nome);

        temp.n_categoria=strlen(categoria);
        temp.categoria=malloc(temp.n_categoria*sizeof(char));
        strcpy(temp.categoria,categoria);

        temp.data=malloc(11*sizeof(char));
        strcpy(temp.data,data);

        return temp;
    }
    return atletaVoid();
}
void atletaPrint(atleta item,FILE *fp){
    fprintf(fp,"Atleta:\n\tCodice:%s \tNome:%s \t Cognome:%s \tData di nascita:%s \n\tCategoria Sportiva:%s \tOre di allenamento:%d\n",item.codice,item.nome,item.cognome,item.data,item.categoria,item.ore);
}
atleta atletaVoid(){
    atleta temp;
    temp.data=malloc(sizeof(char));
    strcpy(temp.data,"\0");
    temp.categoria=malloc(sizeof(char));
    strcpy(temp.categoria,"\0");
    temp.cognome=temp.nome=malloc(sizeof(char));
    strcpy(temp.cognome,"\0");
    temp.codice=malloc(sizeof(char));
    strcpy(temp.codice,"\0");

    temp.n_categoria=temp.n_cognome=temp.n_nome=temp.ore=0;
    return temp;
}
int atletaEq(atleta a,atleta b){
    if(strcmp(a.codice,b.codice)==0){
        return 1;
    }
    else{
        return 0;
    }
}
