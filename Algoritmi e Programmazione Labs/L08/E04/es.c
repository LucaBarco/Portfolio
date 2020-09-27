//
// Created by Luca Barco on 10/12/2017.
//

#include "es.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

esercizio eserScan(FILE *fp){
    esercizio temp;
    if(fscanf(fp,"%s %s %s\n",temp.nome,temp.categoria,temp.tipologia)!=EOF){
        return temp;
    }
    else{
        return eserVoid();
    }
}

int eserEq(esercizio a,esercizio b){
    if(strcmp(a.nome,b.nome)==0){
        return 1;
    }
    else{
        return 0;
    }
}

esercizio eserVoid(){
    esercizio temp;
    char s[1]={'\0'};
    strcpy(temp.nome,s);
    strcpy(temp.categoria,s);
    strcpy(temp.tipologia,s);
    return temp;
}
