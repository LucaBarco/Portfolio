//
// Created by Luca Barco on 10/12/2017.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "atlList.h"
#define MAXC 26

struct nodo_s{
    atleta val;
    link_atleta next;
    link_piano head_piano;
    link_piano tail_piano;
};
struct tabAtleti_s{
    int nAtleti;
    link_atleta head;
    link_atleta tail;
};
tabAtleti nuovaTabAt(){
    tabAtleti a=malloc(sizeof(*a));
    a->head=NULL;
    a->tail=NULL;
    return a;
}
tabAtleti leggiFile_atleta(tabAtleti atleti){
    FILE *fp;
    int i=0;
    atleta temp;
    fp=fopen("atleti.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file 'atleti'!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&(atleti->nAtleti));
    temp=atletaScan(fp);
    while(atletaEq((temp),atletaVoid())!=1 && i<atleti->nAtleti){
        atleti->head=InserimentoCoda(atleti,temp);
        i++;
        temp=atletaScan(fp);
    }
    fclose(fp);
    return atleti;
}
link_atleta nuovoNodo(link_atleta next,atleta val){
    link_atleta x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    x->head_piano=NULL;
    x->tail_piano=NULL;
    return x;
}
link_atleta InserimentoCoda(tabAtleti atleti,atleta val){
    link_atleta x;
    if(atleti->head==NULL) {
        x = nuovoNodo(NULL, val);
        atleti->tail = x;
        return x;
    }
    for(x=atleti->head;x->next!=NULL;x=x->next);
    x->next=nuovoNodo(NULL,val);
    atleti->tail=x->next;
    return atleti->head;
}
tabAtleti rimuoviNodo(tabAtleti atleti,char *k){
    link_atleta x,p;
    if(atleti->head==NULL) {
        return NULL;
    }
    for(x=atleti->head,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->val.codice,k)==0){
            if(x==atleti->head)
                atleti->head=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    return atleti;
}
link_atleta ricercaCodice(tabAtleti atleti,char *chiave){
    link_atleta i;
    link_atleta h=atleti->head;
    for(i=h;i!=NULL;i=i->next){
        if(strcmp(chiave,i->val.codice)==0)
            return i;
    }
    return NULL;
}
link_atleta ricercaCognome(tabAtleti atleti,char *chiave){
    link_atleta i;
    link_atleta h=atleti->head;
    int ls,k,trovato=0;
    char cognome_temp[MAXC];
    ls=strlen(chiave);
    for(k=0;k<=ls;k++){
        chiave[k]=toupper(chiave[k]);
    }
    for(i=h;i!=NULL;i=i->next) {
        strcpy(cognome_temp, i->val.cognome);
        for (k = 0; k <= strlen(cognome_temp); k++) {
            cognome_temp[k] = toupper(cognome_temp[k]);
        }
        if (strncmp(chiave, cognome_temp,ls) == 0) {
            trovato=1;
            printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria, i->val.ore);
        }
    }
    if(trovato==0)
        printf("-----Nessuna corrispondenza trovata!-----\n");

    return NULL;
}
tabAtleti aggiungiAtleta(tabAtleti atleti){
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];
    int i_ore_allenamento;
    atleta temp;
    printf("Inserisci i dati dell'atleta\n\tCodice:");
    scanf("%s",i_codice);
    printf("Nome:");
    scanf("%s",i_nome);
    printf("Cognome:");
    scanf("%s",i_cognome);
    printf("Data di nascita:");
    scanf("%s",i_data);
    printf("Categoria Sportiva:");
    scanf("%s",i_categoria);
    printf("Ore di allenamento settimanali:");
    scanf("%d",&i_ore_allenamento);

    temp.codice=malloc(6*sizeof(char));
    strcpy(temp.codice,i_codice);

    temp.data=malloc(11*sizeof(char));
    strcpy(temp.data,i_data);

    temp.n_nome=strlen(i_nome);
    temp.nome=malloc((temp.n_nome+1)*sizeof(char));
    strcpy(temp.nome,i_nome);

    temp.n_cognome=strlen(i_cognome);
    temp.cognome=malloc((temp.n_cognome+1)*sizeof(char));
    strcpy(temp.cognome,i_cognome);

    temp.n_categoria=strlen(i_categoria);
    temp.categoria=malloc((temp.n_categoria+1)*sizeof(char));
    strcpy(temp.categoria,i_categoria);

    temp.ore=i_ore_allenamento;

    atleti->head= InserimentoCoda(atleti,temp);
    printf("-----Atleta aggiunto correttamente!-----\n");
    return atleti;
}
tabAtleti cancellaAtleta(tabAtleti atleti){
    char codice[6];
    printf("Inserire il codice dell'atleta da eliminare!\n");
    scanf("%s",codice);
    atleti= rimuoviNodo(atleti,codice);
    printf("-----Cancellazione riuscita!-----\n");
    return atleti;
}
void stampaAtleta(tabAtleti atleti,char *chiave){
    link_atleta i;
    link_piano j;
    i=ricercaCodice(atleti,chiave);
    if(i!=NULL){
        printf("---------------Ricerca terminata!---------------\n");
        atletaPrint(i->val,stdout);
        if(i->head_piano!=NULL){
            printf("\n-----> Piano di allenamento:\n");
            for(j=i->head_piano;j!=NULL;j=nextEser(j)){
                stampaEserPiano(j,stdout);
            }
        }
        else{
            printf("-----> Piano relativo all'atleta non trovato!\n");
        }
    }
    else{
        printf("---------------Atleta non trovato!---------------\n");
    }
}
void aggiornaOre(tabAtleti atleti){
    char codice[6];
    int nuove_ore;
    link_atleta i;
    printf("Inserisci il codice dell'atleta di cui aggiornare le ore di allenamento seguito dal nuovo numero di ore");
    scanf("%s %d",codice,&nuove_ore);
    i=ricercaCodice(atleti,codice);
    i->val.ore=nuove_ore;
    printf("---------- Aggiornamento riuscito!----------\n");
    printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
           i->val.ore);
    return;
}
link_atleta trovaCodice(tabAtleti atleti,char *cognome,char *nome){
    char cognome_temp[MAXC],nome_temp[MAXC];
    link_atleta i,l;
    int k,trovato=0,esci=0,scelta;

    for(k=0;k<=strlen(cognome);k++){
        cognome[k]=toupper(cognome[k]);
    }
    for(k=0;k<=strlen(nome);k++){
        nome[k]=toupper(nome[k]);
    }

    for(i=atleti->head;i!=NULL&&trovato==0&&esci==0;i=i->next) {
        trovato=0;
        strcpy(cognome_temp, i->val.cognome);
        for (k = 0; k <= strlen(cognome_temp); k++) {
            cognome_temp[k] = toupper(cognome_temp[k]);
        }
        if (strncmp(cognome, cognome_temp,strlen(cognome_temp)) == 0) {
            strcpy(nome_temp, i->val.nome);
            for (k = 0; k <= strlen(nome_temp); k++) {
                nome_temp[k] = toupper(nome_temp[k]);
            }
            if(strncmp(nome,nome_temp,strlen(nome_temp))==0){
                trovato=1;
                printf("Atleta: %s %s \tCodice: %s\n\tPremere 1 per confermare,0 per cercare altri omonimi\n",i->val.nome,i->val.cognome,i->val.codice);
                scanf("%d",&scelta);
                if(scelta==1) {
                    l = i;
                    esci = 1;
                }
                return l;
            }
        }
    }
    if(trovato==0) {

        printf("-----Nessuna corrispondenza trovata!-----\n");
        l=NULL;
        return l;
    }
}
tabAtleti leggiFile_piano(tabAtleti atleti,char *codice,tabEser vett){
    char nomefile[10];
    link_atleta i;
    link_piano head=newPointPiano();
    link_piano tail=newPointPiano();
    link_piano temp;
    int k,trovato=0;
    FILE *fp;
    i=ricercaCodice(atleti,codice);
    if(i!=NULL) {
        if (i->head_piano == NULL) {
            sprintf(nomefile, "%s.txt", codice);
            fp = fopen(nomefile, "r");
            if (fp == NULL) {
                printf("----> Errore nell'apertura del piano. File non presente!\n");
                return NULL;
            }
            head = NULL;
            while ((temp = eserScanPiano(fp)) != NULL) {
                head = InserimentoCoda_piano(head, &tail, temp);
                tail = associaEser(tail, vett);
            }
            i->head_piano = head;
            i->tail_piano = tail;
            fclose(fp);
            return atleti;
        } else {
            printf("-----------Piano gia' caricato per questo utente!-----------\n");
            return atleti;
        }
    }
    else{
        printf("---------------File piano non presente per questo atleta!---------------\n");
        return atleti;
    }
}

tabAtleti rimuoviEser(tabAtleti atleti,char *codice,char *k){
    link_atleta i=ricercaCodice(atleti,codice);
    i->head_piano=rimuoviEserNodo(i->head_piano,k);
    return atleti;

}

tabAtleti nuovoEser(tabAtleti atleti,char *codice,char *nomees,int set,int rip,tabEser vett){
    link_atleta i=ricercaCodice(atleti,codice);
    link_atleta j;
    int trovato=0;
    link_piano val=newEser(nomees,set,rip,vett);
    val=associaEser(val,vett);
    i->head_piano=InserimentoCoda_piano(i->head_piano,&(i->tail_piano),val);
    for(j=atleti->head;j!=NULL && trovato==0;j=j->next){
        if(strcmp(j->val.codice,codice)==0){
            j->head_piano=i->head_piano;
            trovato=1;
        }
    }
    return atleti;
}

tabAtleti modificaEsAtl(tabAtleti atleti,char *codice_chiave, char *nomees_chiave,int n_set,int n_rip,tabEser vett){
    link_atleta i;
    i=ricercaCodice(atleti,codice_chiave);
    if(i!=NULL){
       i->head_piano=modificaEs(i->head_piano,nomees_chiave,n_rip,n_set,vett);
    }
    else{
        printf("---------------Atleta non trovato!---------------\n");
    }
    return atleti;
}

atleta extractVal(link_atleta i){
    return i->val;
}

int extractRip(link_atleta i,char *nomees,tabEser vett){
    link_piano j;
    for(j=i->head_piano;j!=NULL;j=nextEser(j)){
        if(strcmp(getEserPianoNome(j,vett),nomees)==0){
            return estraiRip(j);
        }
   }
}
int extractSet(link_atleta i,char *nomees,tabEser vett){
    link_piano j;
    for(j=i->head_piano;j!=NULL;j=nextEser(j)){
        if(strcmp(getEserPianoNome(j,vett),nomees)==0){
            return estraiSet(j);
        }
    }
}

char *extractCode(link_atleta i){
    return i->val.codice;
}