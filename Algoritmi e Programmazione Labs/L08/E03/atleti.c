//
// Created by Luca Barco on 10/12/2017.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "esercizi.h"
#include "atleti.h"
#define MAXC 26
link_atleta leggiFile_atleta(tabAtleti *atleti){
    FILE *fp;
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];
    int i_ore_allenamento,i=0;
    atleta temp;
    fp=fopen("atleti.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file 'atleti'!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&(atleti->nAtleti));
    while(fscanf(fp,"%s %s %s %s %s %d",i_codice,i_cognome,i_nome,i_categoria,i_data,&i_ore_allenamento)!=EOF&&i<atleti->nAtleti){

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

        atleti->head=InserimentoCoda(atleti,temp);
        i++;
    }
    fclose(fp);

    return atleti->head;
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

link_atleta InserimentoCoda(tabAtleti *atleti,atleta val){
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

link_atleta rimuoviNodo(link_atleta h,char *k){
    link_atleta x,p;
    if(h==NULL) {
        return NULL;
    }
    for(x=h,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->val.codice,k)==0){
            if(x==h)
                h=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    return h;
}

link_atleta ricercaCodice(tabAtleti *atleti,char *chiave){
    link_atleta i;
    link_atleta h=atleti->head;
    for(i=h;i!=NULL;i=i->next){
        if(strcmp(chiave,i->val.codice)==0)
            return i;
    }
    return NULL;
}

link_atleta ricercaCognome(tabAtleti *atleti,char *chiave){
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
link_atleta aggiungiAtleta(tabAtleti *atleti){
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];
    int i_ore_allenamento;
    atleta temp;
    link_atleta t;
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

    t= InserimentoCoda(atleti,temp);
    atleti->nAtleti++;
    printf("-----Atleta aggiunto correttamente!-----\n");
    return t;
}
link_atleta cancellaAtleta(tabAtleti *atleti){
    link_atleta i;
    char codice[6];
    printf("Inserire il codice dell'atleta da eliminare!\n");
    scanf("%s",codice);
    i= rimuoviNodo(atleti->head,codice);
    atleti->nAtleti--;
    printf("-----Cancellazione riuscita!-----\n");
    return i;
}
void stampaAtleta(tabAtleti *atleti,char *chiave){
    link_atleta i;
    link_piano j;
    i=ricercaCodice(atleti,chiave);
    if(i!=NULL){
        printf("---------------Ricerca terminata!---------------\n");
        printf("Atleta:\n\tCodice:%s \tNome:%s \t Cognome:%s \tData di nascita:%s \n\tCategoria Sportiva:%s \tOre di allenamento:%d\n",i->val.codice,i->val.nome,i->val.cognome,i->val.data,i->val.categoria,i->val.ore);
        if(i->head_piano!=NULL){
            printf("\n-----> Piano di allenamento:\n");
            for(j=i->head_piano;j!=NULL;j=j->next){
                printf("\nNome esercizio:%s \nSet:%d \nRipetizioni:%d\n",j->es->nome,j->set,j->rip);
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
void aggiornaOre(tabAtleti *atleti) {
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
link_atleta trovaCodice(tabAtleti *atleti,char *cognome,char *nome){
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
link_atleta leggiFile_piano(link_atleta h,char *codice,tabEser *vett,link_atleta i){
    char nomefile[10],nomees_temp[MAXN];
    eserPiano_t temp ;
    link_piano head=malloc(sizeof(*head));
    link_piano tail=malloc(sizeof(*tail));

    int k,trovato=0;
    FILE *fp;


    sprintf(nomefile,"%s.txt",codice);
    fp=fopen(nomefile,"r");
    if(fp==NULL){
        printf("----> Errore nell'apertura del piano. File non presente!\n");
        return NULL;
    }
    head=NULL;
    while(fscanf(fp,"%s %d %d\n",nomees_temp,&temp.set,&temp.rip)!=EOF){
        head=InserimentoCoda_piano(head,&tail,temp);
        trovato=0;

        for(k=0;k<vett->n_esercizi && trovato==0;k++){
            if(strcmp(nomees_temp,vett->ElencoEsercizi[k].nome)==0){
                trovato=1;
                tail->es=&vett->ElencoEsercizi[k];
            }
        }
    }
            i->head_piano = head;
            i->tail_piano = tail;


    fclose(fp);

    return h;
}
link_piano nuovoNodo_piano(link_piano next,eserPiano_t val){
    link_piano x;
    x=malloc(sizeof(*x));
    x->set=val.set;
    x->rip=val.rip;
    x->next=next;
    return x;
}
link_piano InserimentoCoda_piano(link_piano h,link_piano *t,eserPiano_t val){
    link_piano i;

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
link_piano modifica_eser(link_atleta h,char *cognome,char *nome,char *nomees,tabEser *esercizi){
    link_piano i;
    int trovato=0;
    int scelta,k;
    eserPiano_t temp;


    printf("Vuoi :\n\t1-Modificare numero di set\n\t2-Modificare numero di ripetizioni\n\t3-Aggiungere esercizio\n\t4-Rimuovere esercizio\n(Inserisci un numero 1->4):");
    scanf("%d",&scelta);

    if(scelta==1){
        printf("Numero di set: ");
        scanf("%d",&temp.set);
    }
    if(scelta==2) {
        printf("Numero di ripetizioni:");
        scanf("%d", &temp.rip);
    }
    if(scelta==1||scelta==2){
        for (i = h->head_piano; i != NULL && trovato == 0; i = i->next) {
            if (strcmp(i->es->nome, nomees) == 0) {
                if(scelta==1) {
                    i->set = temp.set;
                }
                if(scelta==2) {
                    i->rip = temp.rip;
                }
                trovato = 1;
            }
            if (trovato == 0) {
                printf("---------------Esercizio non trovato!---------------\n");
            } else {
                printf("--------------- Modifica eseguita con successo!---------------\n");
                printf("Esercizio: %s \tNuove ripetute:%d \tNuovo set:%d\n", i->es->nome, i->rip, i->set);
            }
        }
        return h->head_piano;
    }
    if(scelta==3){
        //funzione aggiunta esercizio
        printf("Numero di set: ");
        scanf("%d",&temp.set);
        printf("Numero di ripetizioni:");
        scanf("%d",&temp.rip);
        h->head_piano=InserimentoCoda_piano(h->head_piano,&(h->tail_piano),temp);
        for(k=0;k<esercizi->n_esercizi && trovato==0;k++){
            if(strcmp(nomees,esercizi->ElencoEsercizi[k].nome)==0){
                trovato=1;
                h->tail_piano->es=&esercizi->ElencoEsercizi[k];
            }
        }
        if(trovato==0){
            printf("---------------Esercizio non trovato!---------------\n");
        } else {
            printf("--------------- Modifica eseguita con successo!---------------\n");
            printf("Esercizio: %s \tNuove ripetute:%d \tNuovo set:%d\n", h->tail_piano->es->nome, h->tail_piano->rip, h->tail_piano->set);
        }
        return h->head_piano;
    }
    if(scelta ==4){
        //funzione rimuovi esercizio
        for(i=h->head_piano;i!=NULL &&trovato==0;i=i->next){
            if(strcmp(i->es->nome,nomees)==0){
                h->head_piano=rimuoviEser(h,nomees);
                trovato=1;
            }
        }
        if(trovato==0){
            printf("---------------Esercizio non trovato!---------------\n");
        }
        else {
            printf("--------------- Modifica eseguita con successo!---------------\n");
        }
        return h->head_piano;
    }
}
link_piano rimuoviEser(link_atleta i,char *k){
   int trovato=0;
    link_piano x,j;
    for(x=i->head_piano,j=NULL;x!=NULL && trovato==0;j=x,x=x->next){
        if(strcmp(x->es->nome,k)==0){
            if(x==i->head_piano){
                return x->next;
            }
            else{
                j->next=x->next;
            }
            free(x);
            trovato=1;
        }
    }
    return i->head_piano;
}