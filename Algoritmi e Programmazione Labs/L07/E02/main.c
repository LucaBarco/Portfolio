#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXC 26
#define MAXN 51
typedef enum{
    stampa_anagrafica,
    stampa_categoria,
    aggiorna_ore,
    ricerca_codice,
    ricerca_cognome,
    aggiunta_atleta,
    cancella_atleta,
    carica_piano,
    salva_piano,
    modifica_esercizio,
    fine
}comando;

typedef struct esercizio_s{
    char nome[MAXN];
    char categoria[MAXN];
    char tipologia[MAXN];
}esercizio, *p_esercizio;

typedef struct tabEser_s{
    p_esercizio ElencoEsercizi;
    int n_esercizi;
}tabEser;


typedef struct eserPiano_s eserPiano_t,*link_piano;
struct eserPiano_s{
    p_esercizio es;
    int set;
    int rip;
    link_piano next;
};

typedef struct atleta_s{
    char *codice;
    char *nome;
    char *cognome;
    char *categoria;
    char *data;
    int n_nome,n_cognome,n_categoria,ore;
}atleta;

typedef struct nodo_s *link_atleta;
struct nodo_s{
    atleta val;
    link_atleta next;
    link_piano head_piano;
    link_piano tail_piano;
};
typedef struct tabAtleti_s{
    int nAtleti;
    link_atleta head;
    link_atleta tail;
}tabAtleti;

//funzioni relative al tipo di dato atleta
link_atleta leggiFile(tabAtleti *atleti);
link_atleta nuovoNodo(link_atleta next,atleta val);
link_atleta InserimentoCoda(tabAtleti *atleti,atleta val);
link_atleta rimuoviNodo(link_atleta h,char *k);//in base a chiave k
link_atleta ricerca(comando cmd,link_atleta h,char *chiave);
link_atleta aggiungiAtleta(tabAtleti *atleti);
link_atleta cancellaAtleta(tabAtleti *atleti);
void stampaFile(link_atleta h);
void stampaCategoria(tabAtleti *atleti);
void aggiornaOre(tabAtleti *atleti);
link_atleta trovaCodice(tabAtleti *atleti,char *cognome,char *nome);
//funzioni menù
comando leggiComando();

//funzioni relative al tipo di dato esercizio
p_esercizio leggiFile_es(tabEser *esercizi);

//funzioni relative al tipo di dato eserPiano
link_atleta leggiFile_piano(link_atleta h,char *codice,tabEser *vett);
link_piano nuovoNodo_piano(link_piano next,eserPiano_t val);
link_piano InserimentoCoda_piano(link_piano h,link_piano *t,eserPiano_t val);
link_piano modifica_eser(link_piano h,char *nomees_k,int nuoverip,int nuovoset);
void salvaPiano(tabAtleti *atleti,link_atleta i);

int main(){

    link_atleta i;
    char cognome_chiave[MAXC],nome_chiave[MAXC],esercizio_chiave[MAXN],codice_chiave[6];
    int tipostampa,nuoverip,nuovoset,k;
    tabEser *esercizi=malloc(sizeof(tabEser));
    tabAtleti *atleti=malloc(sizeof(tabAtleti));
    comando cmd;
    link_piano j;

    atleti->head=NULL;
    atleti->tail=NULL;

    atleti->head=leggiFile(atleti);
    if(atleti->head==NULL){
        return -1;
    }
    esercizi->ElencoEsercizi=leggiFile_es(esercizi);
    if(esercizi->ElencoEsercizi==NULL){
        return -1;
    }
    //DEBUG!
    for(k=0;k<esercizi->n_esercizi;k++){
        printf("%s\n",esercizi->ElencoEsercizi[k].nome);
    }
    //
    cmd=leggiComando();

    while(cmd!=fine){

        switch(cmd){
            case stampa_anagrafica:
                printf("Effettuare la stampa su:\n\t1-File\n\t2-Schermo\n");
                scanf("%d",&tipostampa);
                if(tipostampa==1){
                    stampaFile(atleti->head);
                }
                else if(tipostampa==2){
                    for(i=atleti->head;i!=NULL;i=i->next) {
                        printf("NOME:%s \tCOGNOME:%s \tDATA DI NASCITA:%s\n",  i->val.nome, i->val.cognome, i->val.data);
                    }
                }
                break;

            case stampa_categoria:
                stampaCategoria(atleti);
                break;
            case aggiorna_ore:
                aggiornaOre(atleti);
                break;
            case ricerca_cognome:
                printf("Inserire il cognome da cercare (anche parziale): ");
                scanf("%s",cognome_chiave);
                ricerca(cmd,atleti->head,cognome_chiave);
                break;

            case ricerca_codice:
                printf("Inserire il codice da cercare: ");
                scanf("%s",codice_chiave);
                i=ricerca(cmd,atleti->head,codice_chiave);
                if(i==NULL){
                    printf("------------Nessuna corrispondenza trovata!------------\n");
                }
                else{
                    printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
                           i->val.ore);
                }
                break;

            case aggiunta_atleta:
                atleti->head=aggiungiAtleta(atleti);
                break;

            case cancella_atleta:
                atleti->head=cancellaAtleta(atleti);
                break;

            case carica_piano:
                printf("Inserisci il codice dell'atleta di cui caricare il piano:");
                scanf("%s",codice_chiave);
                i=ricerca(ricerca_codice,atleti->head,codice_chiave);
                if(i->head_piano==NULL) {
                    atleti->head = leggiFile_piano(atleti->head, codice_chiave, esercizi);
                    printf("---------------Piano caricato correttamente!---------------\n");
                    for(j=atleti->head->head_piano;j!=NULL;j=j->next){
                        printf("%s %d %d\n",j->es->nome,j->set,j->rip);
                    }
                }
                else{
                    printf("-----------Piano gia' caricato per questo utente!-----------\n");
                }
                break;
            case salva_piano:
                printf("Inserisci il codice dell'atleta di cui salvare il piano: ");
                scanf("%s",codice_chiave);
                i=ricerca(ricerca_codice,atleti->head,codice_chiave);
                if(i==NULL||i->head_piano==NULL){
                    printf("Impossibile salvare il piano!\n");
                }
                else {
                    salvaPiano(atleti, i);
                }
                break;
            case modifica_esercizio:
                printf("Inserisci il nome dell'atleta (nome - cognome): ");
                scanf("%s %s",nome_chiave,cognome_chiave);
                printf("%s %s\n",nome_chiave,cognome_chiave);
                printf("Inserisci il nome dell'esercizio da modificare: ");
                scanf("%s",esercizio_chiave);
                printf("Inserire il nuovo numero di set e ripetizioni: ");
                scanf("%d %d",&nuovoset,&nuoverip);
                //funzione di ricerca per cognome a cui aggiungere un controllo sul nome
                i=trovaCodice(atleti,cognome_chiave,nome_chiave);
                if(i!=NULL) {
                    // i = ricerca(ricerca_codice, atleti->head, codice_chiave);
                    if (i->head_piano == NULL) {
                        printf("---------- Piano non presente per questo atleta!----------\n");
                    } else {
                        //se c'è il piano allenamenti controllo che ci sia l'esercizio e modifico i valori richiesti
                        modifica_eser(i->head_piano, esercizio_chiave, nuoverip, nuovoset);

                    }
                }
                break;

            default:
                printf("Comando non valido!\n");
                break;
        }
        cmd=leggiComando();
    }
    for(i=atleti->head;i!=NULL;i=i->next){
        free(i->val.categoria);
        free(i->val.nome);
        free(i->val.cognome);
        free(i->val.codice);
        free(i->val.data);
        free(i);
    }
    free(esercizi);


    return 0;
}

link_atleta leggiFile(tabAtleti *atleti){
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
comando leggiComando(){

    int i=0;
    char temp[20];
    char comandi[11][20]={"stampa_anagrafica","stampa_categoria","aggiorna_ore","ricerca_codice","ricerca_cognome","aggiunta_atleta","cancella_atleta","carica_piano","salva_piano","modifica_esercizio","fine"};
    printf("---------- MENU ----------\n"
                   "\t-stampa_anagrafica : stampa l'anagrafica di tutti gli atleti\n"
                   "\t-stampa_categoria : stampa degli atleti divisi per categoria\n"
                   "\t-aggiorna_ore : aggiorna il monte ore settimanali di un atleta\n"
                   "\t-ricerca_codice : ricerca di un atleta per codice\n"
                   "\t-ricerca_cognome : ricerca di atleti per cognome (anche parziale)\n"
                   "\t-aggiunta_atleta : aggiungi un atleta\n"
                   "\t-cancella_atleta : cancella un atleta dato il codice\n"
                   "\t-carica_piano : carica il piano di allenamenti di un atleta\n"
                   "\t-salva_piano : salva il piano di un atleta\n"
                   "\t-modifica_esercizio : modifica del numero di set/ripetizioni di un esercizio del piano di un atleta\n"
                   "\t-fine\n");
    scanf("%s",temp);
    while(strcmp(temp,comandi[i])!=0 && i<=10){
        i++;
    }
    return i;
}
void stampaFile(link_atleta h){
    FILE *fp;
    link_atleta i;
    char nomefile[MAXC];
    printf("Inserisci il nome del file su cui stampare:");
    scanf("%s",nomefile);

    fp=fopen(nomefile,"w");
    if(fp==NULL){
        printf("Errore nell'apertura del file 'esercizi'!\n");
        return;
    }
    for(i=h;i!=NULL;i=i->next) {
        fprintf(fp,"NOME:%s \tCOGNOME:%s \tDATA DI NASCITA:%s\n",  i->val.nome, i->val.cognome, i->val.data);
    }
    printf("----------Stampa su file effettuata!----------\n");
    fclose(fp);
    return;
}
void stampaCategoria(tabAtleti *atleti){
    char categoria1[MAXC],categoria2[MAXC];
    link_atleta i,j;
    int k,l=0;
    int *stampato=calloc(atleti->nAtleti,sizeof(int));

    for(j=atleti->head;j!=NULL;j=j->next) {
        strcpy(categoria1, j->val.categoria);
        for (k = 0; k <= strlen(categoria1); k++) {
            categoria1[k] = toupper(categoria1[k]);
        }
        printf("\n");
        for (i = atleti->head,l=0; i != NULL; i = i->next,l++) {
            strcpy(categoria2, i->val.categoria);
            for (k = 0; k <= strlen(categoria2); k++) {
                categoria2[k] = toupper(categoria2[k]);
            }
            if (strcmp(categoria1, categoria2) == 0&&stampato[l]==0) {
                stampato[l]=1;
                printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
                       i->val.ore);
            }
        }
    }
}
void aggiornaOre(tabAtleti *atleti){
    char codice[6];
    int nuove_ore;
    link_atleta i;
    printf("Inserisci il codice dell'atleta di cui aggiornare le ore di allenamento seguito dal nuovo numero di ore");
    scanf("%s %d",codice,&nuove_ore);
    i=ricerca(ricerca_codice,atleti->head,codice);
    i->val.ore=nuove_ore;
    printf("---------- Aggiornamento riuscito!----------\n");
    printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
           i->val.ore);
    return;
}
link_atleta ricerca(comando cmd,link_atleta h,char *chiave){
    link_atleta i;
    int ls,k,trovato=0;
    char cognome_temp[MAXC];
    ls=strlen(chiave);

    switch(cmd){
        case ricerca_cognome:
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
                    printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data,
                           i->val.categoria,
                           i->val.ore);
                }
            }
            if(trovato==0)
                printf("-----Nessuna corrispondenza trovata!-----\n");

            return NULL;


        case ricerca_codice:
            for(i=h;i!=NULL;i=i->next){
                if(strcmp(chiave,i->val.codice)==0)
                    return i;
            }
            return NULL;
    }

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
link_atleta leggiFile_piano(link_atleta h,char *codice,tabEser *vett){

    char nomefile[10],nomees_temp[MAXN];
    eserPiano_t temp ;
    link_piano head=malloc(sizeof(*head));
    link_piano tail=malloc(sizeof(*tail));
    link_atleta i;
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

    for(i=h;i!=NULL;i=i->next) {
        if (strcmp(i->val.codice, codice) == 0) {
            i->head_piano = head;
            i->tail_piano = tail;
        }
    }
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

link_piano modifica_eser(link_piano h,char *nomees_k,int nuoverip,int nuovoset){
    link_piano i;
    int trovato=0;
    for(i=h;i!=NULL&&trovato==0;i=i->next){
        if(strcmp(i->es->nome,nomees_k)==0){
            i->set=nuovoset;
            i->rip=nuoverip;
            trovato=1;

        }
        if(trovato==0){
            printf("Esercizio non trovato!\n");
        }
        else{
            printf("---------- Modifica eseguita con successo!----------\n");
            printf("Esercizio: %s \tNuove ripetute:%d \tNuovo set:%d\n",i->es->nome,i->rip,i->set);
        }
    }
    return h;
}
void salvaPiano(tabAtleti *atleti, link_atleta i){
    char nomefile[10];
    FILE *fp;
    link_piano j;

    sprintf(nomefile,"%s.txt",i->val.codice);
    fp=fopen(nomefile,"w");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return;
    }
    for(j=i->head_piano;j!=NULL;j=j->next){
        fprintf(fp,"%s %d %d\n",j->es->nome,j->set,j->rip);
    }
    fclose(fp);
    printf("---------------Stampa su file effettuata!---------------\n");
    return;
}