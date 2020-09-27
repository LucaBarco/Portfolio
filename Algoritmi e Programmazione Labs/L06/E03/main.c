#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXC 26

typedef enum{
    stampa_anagrafica,
    stampa_categoria,
    aggiorna_ore,
    ricerca_codice,
    ricerca_cognome,
    aggiunta_atleta,
    cancella_atleta,
    fine
}comando;

typedef struct atleta_s{
    char *codice;
    char *nome;
    char *cognome;
    char *categoria;
    char *data;
    int n_nome,n_cognome,n_categoria,ore;
}atleta;

typedef struct nodo_s *link;
struct nodo_s{
    atleta val;
    link next;
};

link leggiFile(link h,int *n);
link nuovoNodo(link next,atleta val);
link InserimentoCoda(link h,atleta val);
link rimuoviNodo(link h,char *k);
comando leggiComando();
void stampaFile(link h);
void stampaCategoria(link h,int n);
void aggiornaOre(link head);
link ricerca(comando cmd,link h,char *chiave);
link aggiungiAtleta(link h);
link cancellaAtleta(link h);

int main() {
    link head=NULL;
    link i;
    char cognome_chiave[MAXC],codice_chiave[6];
    int n_atleti,tipostampa;
    comando cmd;
    head=leggiFile(head,&n_atleti);
    cmd=leggiComando();

    while(cmd!=fine){

        switch(cmd){
            case stampa_anagrafica:
                printf("Effettuare la stampa su:\n\t1-File\n\t2-Schermo\n");
                scanf("%d",&tipostampa);
                if(tipostampa==1){
                    stampaFile(head);
                }
                else if(tipostampa==2){
                    for(i=head;i!=NULL;i=i->next) {
                        printf("NOME:%s \tCOGNOME:%s \tDATA DI NASCITA:%s\n",  i->val.nome, i->val.cognome, i->val.data);
                    }
                }

                break;
            case stampa_categoria:
                stampaCategoria(head,n_atleti);
                break;
            case aggiorna_ore:
                aggiornaOre(head);
                break;
            case ricerca_cognome:
                printf("Inserire il cognome da cercare (anche parziale): ");
                scanf("%s",cognome_chiave);
                ricerca(cmd,head,cognome_chiave);


                break;
            case ricerca_codice:
                printf("Inserire il codice da cercare: ");
                scanf("%s",codice_chiave);
                i=ricerca(cmd,head,codice_chiave);
                if(i==NULL){
                    printf("-----Nessuna corrispondenza trovata!-----\n");
                }
                else{
                printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
                       i->val.ore);
                }
                break;
            case aggiunta_atleta:
                 head=aggiungiAtleta(head);
                break;
            case cancella_atleta:
                 head=cancellaAtleta(head);
                break;
        }
    cmd=leggiComando();
    }
    for(i=head;i!=NULL;i=i->next){
        free(i->val.categoria);
        free(i->val.nome);
        free(i->val.cognome);
        free(i->val.codice);
        free(i->val.data);
        free(i);
    }


    return 0;
}

link leggiFile(link h,int *n){
    FILE *fp;
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];
    int i_ore_allenamento,i=0,N;
   atleta temp;
    fp=fopen("atleti.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&N);

    while(fscanf(fp,"%s %s %s %s %s %d",i_codice,i_cognome,i_nome,i_categoria,i_data,&i_ore_allenamento)!=EOF&&i<N){

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

        h=InserimentoCoda(h,temp);
      i++;
    }
    fp=fclose(fp);
*n=N;
return h;
}
link nuovoNodo(link next,atleta val){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    return x;
}
link InserimentoCoda(link h,atleta val){
    link x;
    if(h==NULL)
        return nuovoNodo(NULL,val);
        for(x=h;x->next!=NULL;x=x->next);
            x->next=nuovoNodo(NULL,val);
            return h;
    }
link rimuoviNodo(link h,char *k){
    link x,p;
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
    char comandi[8][20]={"stampa_anagrafica","stampa_categoria","aggiorna_ore","ricerca_codice","ricerca_cognome","aggiunta_atleta","cancella_atleta","fine"};
    printf("---------- MENU ----------\n"
                   "\t-stampa_anagrafica : stampa l'anagrafica di tutti gli atleti\n"
                   "\t-stampa_categoria : stampa degli atleti divisi per categoria\n"
                   "\t-aggiorna_ore : aggiorna il monte ore settimanali di un atleta\n"
                   "\t-ricerca_codice : ricerca di un atleta per codice\n"
                   "\t-ricerca_cognome : ricerca di atleti per cognome (anche parziale)\n"
                   "\t-aggiunta_atleta : aggiungi un atleta\n"
                   "\t-cancella_atleta : cancella un atleta dato il codice\n"
                   "\t-fine\n");
    scanf("%s",temp);
    while(strcmp(temp,comandi[i])!=0 && i<=7){
        i++;
    }
    return i;
}
void stampaFile(link h){
    FILE *fp;
    link i;
    char nomefile[MAXC];
    printf("Inserisci il nome del file su cui stampare:");
    scanf("%s",nomefile);

    fp=fopen(nomefile,"w");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return;
    }
    for(i=h;i!=NULL;i=i->next) {
        fprintf(fp,"NOME:%s \tCOGNOME:%s \tDATA DI NASCITA:%s\n",  i->val.nome, i->val.cognome, i->val.data);
    }
    printf("----------Stampa su file effettuata!----------\n");
    fp=fclose(fp);
    return;
}
void stampaCategoria(link h,int n){
    char categoria1[MAXC],categoria2[MAXC];
    link i,j;
    int k,l=0;
    int *stampato=calloc(n,sizeof(int));

for(j=h;j!=NULL;j=j->next) {
    strcpy(categoria1, j->val.categoria);
    for (k = 0; k <= strlen(categoria1); k++) {
        categoria1[k] = toupper(categoria1[k]);
    }
    printf("\n");
    for (i = h,l=0; i != NULL; i = i->next,l++) {
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
void aggiornaOre(link h){
    char codice[6];
    int nuove_ore;
    link i;
    printf("Inserisci il codice dell'atleta di cui aggiornare le ore di allenamento seguito dal nuovo numero di ore");
    scanf("%s %d",codice,&nuove_ore);
    i=ricerca(ricerca_codice,h,codice);
    i->val.ore=nuove_ore;
    printf("---------- Aggiornamento riuscito!----------\n");
    printf("%s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.data, i->val.categoria,
           i->val.ore);
    return;
}
link ricerca(comando cmd,link h,char *chiave){
    link i;
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
link aggiungiAtleta(link h){
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];
    int i_ore_allenamento;
    atleta temp;
    link t;
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

    t= InserimentoCoda(h,temp);
    printf("-----Atleta aggiunto correttamente!-----\n");
    return t;
}
link cancellaAtleta(link h){
    link i;
    char codice[6];
    printf("Inserire il codice dell'atleta da eliminare!\n");
    scanf("%s",codice);
    i= rimuoviNodo(h,codice);
    printf("-----Cancellazione riuscita!-----\n");
    return i;

}

