//
// Created by Luca Barco on 10/12/2017.
//
#include <stdlib.h>
#include <string.h>
#include "esList.h"
#ifndef MAXC
#define MAXC 26
#endif
struct eserPiano_s{
    int es;
    char nomees[MAXC];
    int set;
    int rip;
    link_piano next;
};
link_piano newPointPiano(){
    link_piano a=malloc(sizeof(*a));
    return a;
}
link_piano eserScanPiano(FILE *fp){
    link_piano temp=malloc(sizeof(*temp));

    if(fscanf(fp,"%s %d %d\n",temp->nomees,&temp->set,&temp->rip)!=EOF){

        return temp;
    }
    else{
        return NULL;
    }
}
link_piano eserPianoVoid(){
    link_piano temp=malloc(sizeof(*temp));
    temp->rip=0;
    temp->next=NULL;
    temp->es=0;
    temp->set=0;
    strcpy(temp->nomees,"\0");
    return NULL;
}
link_piano associaEser(link_piano t,tabEser esercizi){
    int k,n,trovato=0;
    n=contaEser(esercizi);
    for(k=0;k<n && trovato==0;k++){
        if(strcmp(t->nomees,nomeGetEser(esercizi,k))==0){
            trovato=1;
            t->es=k;
        }
    }
    return t;
}
link_piano nuovoNodo_piano(link_piano next,link_piano val){
    link_piano x;
    x=malloc(sizeof(*x));
    x->set=val->set;
    x->rip=val->rip;
    x->next=next;
    strcpy(x->nomees,val->nomees);
    x->es=val->es;
    return x;
}
link_piano InserimentoCoda_piano(link_piano h,link_piano *t,link_piano val){
    link_piano i;
    int k;
    if(h==NULL){
        i= nuovoNodo_piano(NULL,val);
        *t=i;
        return i;
    }
    for(i=h;i->next!=NULL;i=i->next);
    i->next=nuovoNodo_piano(NULL,val);
    *t=i->next;
    return h;
}
link_piano rimuoviEserNodo(link_piano h,char *k) {
   link_piano x,j;
    int trovato=0;
    for(x=h,j=NULL;x!=NULL && trovato==0;j=x,x=x->next){
        if(strcmp(x->nomees,k)==0){
            if(x==h){
                return x->next;
            }
            else{
                j->next=x->next;
            }
            free(x);
            trovato=1;
        }
    }
    return h;
}
link_piano nextEser(link_piano t){
    return t->next;
}
void stampaEserPiano(link_piano t,FILE *fp){
    fprintf(fp,"\nNome esercizio:%s \n\tSet:%d \nRipetizioni:%d\n",t->nomees,t->set,t->rip);
}
char *getEserPianoNome(link_piano t,tabEser vett){
    //estrazione del nome
    return nomeGetEser(vett,t->es);
}
link_piano modificaEs(link_piano h,char *nomees_chiave,int n_rip,int n_set,tabEser vett){
    link_piano i;
    int trovato=0;
    for(i=h;i!=NULL && trovato==0;i=nextEser(i)){
        if(strcmp(getEserPianoNome(i,vett),nomees_chiave)==0){
            trovato=1;
            i->set=n_set;
            i->rip=n_rip;
        }
    }
    return h;
}
link_piano newEser(char *nomees,int set,int rip,tabEser vett){
    link_piano val=malloc(sizeof(*val));
    strcpy(val->nomees,nomees);
    val->rip=rip;
    val->set=set;
    val=associaEser(val,vett);
    return val;
}
int estraiRip(link_piano i){
    return i->rip;
}
int estraiSet(link_piano i){
    return i->set;
}