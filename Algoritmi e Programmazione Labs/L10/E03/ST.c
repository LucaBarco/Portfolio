//
// Created by Luca Barco on 08/01/2018.
//

#include "ST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 30
#define Mprimo 17 //settandolo a 29 NON VA
typedef struct node{
    char nome[MAX];
    char id_rete[MAX];
}node;
struct st{
    node *elenco;
    int N;
    int M;
};
int STsize(int maxN){
    int primes[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int i=0,maxallowed=primes[15]/2;
    if(maxN<maxallowed){
        for(i=0;i<16;i++){
            if(2*maxN<=primes[i])
                return primes[i];
        }
    }
    return -1;
}
ST STinit(int M) {

    ST symboltable = malloc(sizeof(*symboltable));
    symboltable->M=STsize(M);
    symboltable->elenco = malloc(symboltable->M * sizeof(node));
    int i;
    for (i = 0; i < symboltable->M; i++) {
        strcpy(symboltable->elenco[i].nome,"\0");
    }
    symboltable->N=0;
    return symboltable;
}

static int hash(char *v,int M){
    int h=0,base=127;
    for(;*v!='\0';v++)
        h=(base*h+*v)%M;
    return h;
}

int full(ST st,int j){
    if(strcmp(st->elenco[j].nome,"\0")==0){
        return 0;
    }
    return 1;
}

int STinsert(ST st,char *id1,char *id2){
    char temp[MAX],*id;
    strcpy(temp,id1);
    int j;
    j=hash(temp,st->M);
    while(full(st,j)==1) {
        j = (j + 1) % st->M;
    }
    id=strcpy(st->elenco[j].nome,id1);
    printf("%s\n",st->elenco[j].nome);
    strcpy(st->elenco[j].id_rete,id2);
    st->N++;
    //printf("In tab[%d]: \t",j);
    //printf("%s\t",st->elenco[j].nome);
    //printf("%s\n",st->elenco[j].id_rete);
    return j;
}

int STsearch(ST st,char *k){
    char temp[MAX],tentativi=0;
    strcpy(temp,k);
    int i=hash(temp,st->M);
    while(full(st,i)==1) {
        if (strcmp(st->elenco[i].nome, k) == 0) {
            return i;
        } else {
            i = (i + 1) % st->M;
        }
    }
    return -1;
}

char * STretrieveNome(ST st,int i){
    return st->elenco[i].nome;
}
char * STretrieveRete(ST st,int i){
    return st->elenco[i].id_rete;
}

void STprint(ST st){
    int i;
    for(i=0;i<st->M;i++){
        if(full(st,i)==1)
           // printf("tab[%d]:",i+1);
        printf("%s\n",st->elenco[i].nome);
    }
}