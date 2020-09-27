#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXC 26

 struct data_s {
    int giorno;
    int mese;
    int anno;
};

typedef struct atleta_s{
    char *codice;
    char *nome;
    int n_nome;
    char *cognome;
    int n_cognome;
    char *categoria;
    int n_categoria;
    char *data;
    int ore_allenamento;
    char *chiave;
    int n_chiave;
}atleta;
typedef enum{
    stampa_anagrafica,
    ordina_nascita,
    ordina_codice,
    ordina_cognome,
    stampa_categoria,
    aggiorna_ore,
    ricerca_codice,
    ricerca_cognome,
    fine
}comando;

atleta * leggiFile(FILE *fp, atleta *v,int *n);
comando leggiComando();
void stampaElenco(atleta *v,int N,int tipo_stampa);
atleta * selezionaChiave(comando cmd, atleta *v, int n);
void ordinamento(comando cmd, atleta *v,int n);
void MergeSort(atleta *v,atleta *B,int l,int r,comando cmd);
void Merge(atleta *v, atleta *B,int l,int q,int r,comando cmd);
int confrontaChiave(comando cmd, atleta *v,int i,int j);
void aggiornaOre(atleta *elenco,int n,int *ordine);
int ricercaLineare(char *key,atleta *v,int n);
int ricercaDicotomica(char *key, atleta *v, int n);
void stampaCategoria(atleta *v,int n);
char* aggiustaData(struct data_s nascita1);
void ricercaNuoveOccorrenze(int j,char *chiave,atleta *v,int n,int tipo);
int main() {

    FILE*fp;
    atleta *elenco;
    int n_atleti;
    comando cmd;
    int tipo_stampa; //1 se su file, 2 se su schermo
    int ordine[3]={0,0,0};//vettore di flag per tenere traccia dell'ordinamento del vettore e rispetto a quale chiave :
                        // elemento 0-> nascita | elemento 1-> codice | elemento 2 -> cognome
    char codice_chiave[6];
    char cognome_chiave[MAXC];
    int tiporicerca; //1 se lineare, 2 se dicotomica
    int nuove_ore;
    int j,k;

    elenco=leggiFile(fp,elenco,&n_atleti);

    if((n_atleti)==-1){
        return 0;
    }

    cmd=leggiComando();
    while(cmd!=fine) {
        switch (cmd) {
            case stampa_anagrafica:
                //stampa dell'anagrafica degli atleti su file o a schermo
                printf("Effettuare la stampa su: \n\t1 - file\n\t2-schermo\nInserire numero:");
                scanf("%d", &tipo_stampa);
                stampaElenco(elenco, n_atleti, tipo_stampa);
                break;
            case ordina_nascita:
                //ordina l'elenco per data di nascita e poi lo stampa
                elenco=selezionaChiave(cmd,elenco,n_atleti);
                ordinamento(cmd,elenco,n_atleti);
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",elenco[j].codice,elenco[j].nome,elenco[j].cognome,elenco[j].data,elenco[j].categoria,elenco[j].ore_allenamento);
                }
                ordine[0] = 1;
                for(k=1;k<3 ;k++){
                    ordine[k]=0;
                }
                break;
            case ordina_codice:
                //ordina l'elenco per codice e poi lo stampa
                elenco=selezionaChiave(cmd,elenco,n_atleti);
                ordinamento(cmd,elenco,n_atleti);
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",elenco[j].codice,elenco[j].nome,elenco[j].cognome,elenco[j].data,elenco[j].categoria,elenco[j].ore_allenamento);
                }
                ordine[1] = 1;
                for(k=1;k<3 ;k++){
                    if(k!=1)
                        ordine[k]=0;
                }
                break;
            case ordina_cognome:
                //ordina l'elenco in ordine alfabetico e poi lo stampa
                elenco=selezionaChiave(cmd,elenco,n_atleti);
                ordinamento(cmd,elenco,n_atleti);
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",elenco[j].codice,elenco[j].nome,elenco[j].cognome,elenco[j].data,elenco[j].categoria,elenco[j].ore_allenamento);
                }
                ordine[2] = 1;
                for(k=1;k<3 ;k++){
                    if(k!=2)
                        ordine[k]=0;
                }
                break;
            case stampa_categoria:
                //stampa degli atleti divisi in base alla categoria
                selezionaChiave(cmd,elenco,n_atleti);
                ordinamento(cmd,elenco,n_atleti);
                stampaCategoria(elenco,n_atleti);
                break;

            case aggiorna_ore:
               //aggiorna le ore di allenamento di un atleta
                selezionaChiave(cmd,elenco,n_atleti);
                aggiornaOre(elenco,n_atleti,ordine);
                break;

            case ricerca_codice:
                //ricerca di un atleta per codice
                selezionaChiave(cmd,elenco,n_atleti);
                printf("Inserire il codice da ricercare: ");
                scanf("%s", codice_chiave);
                if(ordine[0]==1){
                    j=ricercaDicotomica(codice_chiave,elenco,n_atleti);
                }
                else{
                   j= ricercaLineare(codice_chiave,elenco,n_atleti);
                }
                printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",elenco[j].codice,elenco[j].nome,elenco[j].cognome,elenco[j].data,elenco[j].categoria,elenco[j].ore_allenamento);
                break;

            case ricerca_cognome:
                //ricerca di un atleta per cognome e stampo tutte le occorrenze che trovo
                selezionaChiave(cmd,elenco,n_atleti);
                printf("Inserire il cognome da ricercare (anche parziale): \n");
                scanf("%s", cognome_chiave);
                if(ordine[2]==0){
                   j= ricercaLineare(cognome_chiave, elenco, n_atleti);
                    tiporicerca=1;
                    }
                else {
                    j = ricercaDicotomica(cognome_chiave, elenco, n_atleti);
                    tiporicerca=2;
                }
                    if (j == -1) {
                        printf("Cognome non trovato!\n");
                    } else {
                        printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                               elenco[j].codice, elenco[j].nome, elenco[j].cognome, elenco[j].data, elenco[j].categoria,
                               elenco[j].ore_allenamento);
                        ricercaNuoveOccorrenze(j,cognome_chiave,elenco,n_atleti,tiporicerca);
                    }

                break;

            default:
                printf("Comando non valido!\n");

        }
        cmd=leggiComando();
    }
    for(j=0;j<n_atleti;j++){
        free(elenco[j].nome);
        free(elenco[j].cognome);
        free(elenco[j].categoria);
        free(elenco[j].codice);
        free(elenco[j].data);
        free(elenco[j].chiave);
    }
    free(elenco);
    return 0;
}

atleta *  leggiFile(FILE *fp, atleta *v,int *n){
    //leggo il file atleti.txt e lo salvo in un vettore di struct atleta allocato dinamicamente

    int N,i=0;
    char i_codice[6];
    char i_nome[MAXC];
    char i_cognome[MAXC];
    char i_categoria[MAXC];
    char i_data[11];


    if((fp=fopen("atleti.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
        *n=-1;
        return NULL;
    }
    fscanf(fp,"%d",&N);
    v=(atleta *)malloc(N*sizeof(atleta));

    while(fscanf(fp,"%s %s %s %s %s %d",i_codice,i_cognome,i_nome,i_categoria,i_data,&v[i].ore_allenamento)!=EOF&&i<N){

        v[i].codice=malloc(6*sizeof(char));
        strcpy(v[i].codice,i_codice);

        v[i].data=malloc(11*sizeof(char));
        strcpy(v[i].data,i_data);

        v[i].n_nome=strlen(i_nome);
        v[i].nome=malloc((v[i].n_nome+1)*sizeof(char));
        strcpy(v[i].nome,i_nome);

        v[i].n_cognome=strlen(i_cognome);
        v[i].cognome=malloc((v[i].n_cognome+1)*sizeof(char));
        strcpy(v[i].cognome,i_cognome);

        v[i].n_categoria=strlen(i_categoria);
        v[i].categoria=malloc((v[i].n_categoria+1)*sizeof(char));
        strcpy(v[i].categoria,i_categoria);

        i++;
    }
    *n=N;
return v;
}

comando leggiComando(){

    char tabella[9][20]={"stampa_anagrafica", "ordina_nascita", "ordina_codice",
                      "ordina_cognome", "stampa_categoria", "aggiorna_ore",
                      "ricerca_codice", "ricerca_cognome", "fine"};
    int i=0;
    char s[MAXC];
    printf("\n----------MENU----------\n");
    printf("\t- stampa_anagrafica :stampa i contenuti dell'anagrafica degli atleti\n"
                   "\t- ordina_nascita :ordina l'elenco per data di nascita\n"
                   "\t- ordina_codice :ordina l'elenco per codice identificativo\n"
                   "\t- ordina_cognome :ordina l'elenco per cognome\n"
                   "\t- stampa_categoria :stampa l'elenco per categoria di sport\n"
                   "\t- aggiorna_ore : aggiorna il numero di ore di allenameno settimanali di un atleta\n"
                   "\t- ricerca_codice : ricerca di un atleta per codice identificativo\n"
                   "\t- ricerca_cognome :ricerca di un atleta per cognome (anche parziale)\n"
                   "\t- fine \n");
    scanf("%s",s);
    while(strcmp(tabella[i],s)!=0 && i<=8){
        i++;
    }
    return i;
}

void stampaElenco(atleta *v,int N,int tipo_stampa){

    int i;
    char nomefile[MAXC];
    FILE *fp;
    if(tipo_stampa==1) {
        printf("Inserire il nome del file di output: (formato nomefile.txt)\n");
        scanf("%s",nomefile);
        if((fp=fopen(nomefile,"w"))==NULL){
            printf("Errore nell'apertura del file!\n");
            return;
        }
        for (i = 0; i < N; i++) {
            fprintf(fp,"\n\tNome:%s \tCognome:%s \tData di nascita: %s", v[i].nome, v[i].cognome, v[i].data);
        }
        printf("---------- Stampa su file effettuata!----------\n");
        fp=fclose(fp);
    }
    if(tipo_stampa==2) {
        for (i = 0; i < N; i++) {
            printf("\n\tNome:%s \tCognome:%s \tData di nascita: %s", v[i].nome, v[i].cognome, v[i].data);
        }
    }
return;
}

atleta * selezionaChiave(comando cmd, atleta *v, int n){

    int i;

    switch(cmd){
        case ordina_codice:
        case aggiorna_ore:
        case ricerca_codice:
            for(i=0;i<n;i++){
                v[i].chiave=malloc(6*sizeof(char));
                strcpy(v[i].chiave,v[i].codice);
                v[i].n_chiave=6;
            }
            break;

        case ordina_nascita:

            for(i=0;i<n;i++){
                v[i].chiave=malloc(11*sizeof(char));
                strcpy(v[i].chiave,v[i].data);
                v[i].n_chiave=11;
            }
            break;

        case ordina_cognome:
        case ricerca_cognome:
            for(i=0;i<n;i++){
                v[i].chiave=malloc((v[i].n_cognome+1)*sizeof(char));
                strcpy(v[i].chiave,v[i].cognome);
                v[i].n_chiave=v[i].n_cognome;
            }
            break;

        case stampa_categoria:
            for(i=0;i<n;i++){
                v[i].chiave=malloc((v[i].n_categoria+1)*sizeof(char));
                strcpy(v[i].chiave,v[i].categoria);
                v[i].n_chiave=strlen(v[i].chiave);
            }
            break;


    }

    return v;


}

void ordinamento(comando cmd, atleta *v,int n){
    //wrapper
    int l=0,r=n-1;
    atleta *B=malloc(n*sizeof(atleta));
    MergeSort(v,B,l,r,cmd);
}

void MergeSort(atleta *v,atleta *B,int l,int r,comando cmd){

    int q=(r+l)/2;
    if(l>=r)
        return;
    MergeSort(v,B,l,q,cmd);
    MergeSort(v,B,q+1,r,cmd);
    Merge(v,B,l,q,r,cmd);
}

void Merge(atleta *v, atleta *B,int l,int q,int r,comando cmd){
    int i=l,j=q+1,k;
    for(k=l;k<=r;k++){
        if(i>q){
            B[k]=v[j];
        j++;
        }
        else if (j>r){
            B[k]=v[i];
            i++;
        }
        else if(confrontaChiave(cmd,v,i,j)<=0){
            B[k]=v[i];
            i++;
        }
        else{
            B[k]=v[j];
            j++;
        }
    }
    for(k=l;k<=r;k++){
        v[k]=B[k];
    }
}

int confrontaChiave(comando cmd, atleta *v,int i,int j){

    struct data_s nascita1,nascita2;
    char *data_1,*data_2;
    char nome1[MAXC],nome2[MAXC];
    int k;
    switch (cmd){
        case ordina_nascita:
            sscanf(v[i].data,"%d/%d/%d",&nascita1.giorno,&nascita1.mese,&nascita1.anno);
            data_1=aggiustaData(nascita1);
            sscanf(v[j].data,"%d/%d/%d",&nascita2.giorno,&nascita2.mese,&nascita2.anno);
            data_2=aggiustaData(nascita2);
            return strcmp(data_1,data_2);

        case ordina_cognome:
            //case sensitive
            for(k=0;k<=v[i].n_cognome;k++){
                v[i].chiave[k]=toupper(v[i].chiave[k]);
            }
            for(k=0;k<=v[j].n_cognome;k++){
                v[j].chiave[k]=toupper(v[j].chiave[k]);
            }

            if(strcmp(v[i].chiave,v[j].chiave)==0) {

                strcpy(nome1, v[i].nome);
                strcpy(nome2, v[j].nome);
                for (k = 0; k <= v[i].n_nome; k++) {
                    nome1[k]=toupper(nome1[k]);
                }
                for (k = 0; k <= v[j].n_nome; k++) {
                    nome2[k]=toupper(nome2[k]);
                }

                return strcmp(nome1, nome2);
            }
            return strcmp(v[i].chiave,v[j].chiave);

        default:
            for(k=0;k<=v[i].n_chiave;k++){
               v[i].chiave[k]= toupper(v[i].chiave[k]);
            }
            for(k=0;k<=v[j].n_chiave;k++){
               v[j].chiave[k]= toupper(v[j].chiave[k]);
            }
            return strcmp(v[i].chiave,v[j].chiave);

    }

}

int ricercaLineare(char *key,atleta *v,int n){

    int i,k;
    int ls=strlen(key);//suppongo che la lunghezza della chiave sia sempre minore o uguale a quella dell'elemento con cui si va a confrontare

    for(k=0;k<=ls;k++) {
         key[k]=toupper(key[k]);
    }
    for(i=0;i<n;i++){
        //case sensitive
        for(k=0;k<=v[i].n_chiave;k++) {
           v[i].chiave[k]=toupper(v[i].chiave[k]);
        }

        if(strncmp(key,v[i].chiave,ls)==0){
           return i;
        }
    }
    return -1;
}


int ricercaDicotomica(char *key, atleta *v, int n){
    int l=0,r=n-1;
    int m=l+(r-l)/2;
    int ls=strlen(key);  //suppongo che la lunghezza della chiave sia sempre minore o uguale a quella dell'elemento con cui si va a confrontare
    int status,k;
    for(k=0;k<=ls;k++) {
        key[k]=toupper(key[k]);
    }
    while(l<=r){
        //case sensitive
        for(k=0;k<=v[m].n_chiave;k++) {
            v[m].chiave[k]=toupper(v[m].chiave[k]);
        }
    status=strncmp(key,v[m].chiave,ls);
        if(status==0){
            return m;
        }
        if(status>0){
            l=m+1;
        }
        if(status<0){
            r=m-1;
        }
        m=l+(r-l)/2;
    }

return -1;
}
void aggiornaOre(atleta *elenco,int n,int *ordine) {
    int j;
    int nuove_ore;
    char codice_chiave[MAXC];
    printf("Inserire il codice dell'atleta di cui aggiornare il monte ore settimanali seguito dal nuovo numero di ore:\n");
    scanf("%s %d", codice_chiave, &nuove_ore);
        if (ordine[0] == 1) {
        j = ricercaDicotomica(codice_chiave, elenco, n);
    } else {
        j = ricercaLineare(codice_chiave, elenco, n);
    }
    elenco[j].ore_allenamento = nuove_ore;
    printf("----------Aggiornamento riuscito!----------\n");
    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
           elenco[j].codice, elenco[j].nome, elenco[j].cognome, elenco[j].data, elenco[j].categoria,
           elenco[j].ore_allenamento);

}
void stampaCategoria(atleta *v,int n) {

    int i = 0,k;
    char categoria_temp1[MAXC],categoria_temp2[MAXC];

    for (i = 0; i < n; i++) {
        strcpy(categoria_temp2,v[i].categoria);
        for(k=0;k<=v[i].n_categoria;k++){
            categoria_temp2[k]=toupper(categoria_temp2[k]);
        }
        if (strcmp(categoria_temp1, categoria_temp2) == 0) {
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
                   v[i].codice, v[i].nome, v[i].cognome, v[i].data, v[i].categoria, v[i].ore_allenamento);
        } else {
            printf("\nCategoria: %s\n",v[i].categoria);
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
                   v[i].codice, v[i].nome, v[i].cognome, v[i].data, v[i].categoria, v[i].ore_allenamento);
            strcpy(categoria_temp1, v[i].categoria);
            for(k=0;k<=v[i].n_categoria;k++){
                categoria_temp1[k]=toupper(categoria_temp1[k]);
            }
        }

    }
}
char* aggiustaData(struct data_s nascita1){

    char *data=malloc(11*sizeof(char));
    if(nascita1.giorno<10&&nascita1.mese<10){
        sprintf(data, "%d/0%d/0%d", nascita1.anno, nascita1.mese, nascita1.giorno);
    }
    else if(nascita1.giorno<10) {
        sprintf(data, "%d/%d/0%d", nascita1.anno, nascita1.mese, nascita1.giorno);
    }
    else if(nascita1.mese<10){
        sprintf(data, "%d/0%d/%d", nascita1.anno, nascita1.mese, nascita1.giorno);
    }
    else{
        sprintf(data, "%d/%d/%d", nascita1.anno, nascita1.mese, nascita1.giorno);
    }
    return data;

}
void ricercaNuoveOccorrenze(int j,char *key,atleta *v,int n,int tipo) {

    int i, k, ls, finito = 0;
    char chiave[MAXC];
    ls = strlen(key);
    for (k = 0; k <= ls; k++) {
        key[k] = (char) toupper(key[k]);
    }
    if(tipo==1){
        //continuo la ricerca lineare
        for (i = j + 1; i < n; i++) {
            strcpy(chiave, v[i].cognome);
            for (k = 0; k <= (v[i].n_cognome); k++) {
                chiave[k] = (char) toupper(chiave[k]);
            }
            if (strncmp(key, chiave, ls) == 0) {
                printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                       v[i].codice, v[i].nome, v[i].cognome, v[i].data, v[i].categoria,
                       v[i].ore_allenamento);
            }

        }

    }
    if (tipo == 2) {
        //vado a dx e a sx dell'occorrenza trovata dalla ricerca dicotomica, termino al primo elemento diverso che trovo
        for (i = j + 1; i < n && finito == 0; i++) {
            strcpy(chiave, v[i].cognome);
            for (k = 0; k <= (v[i].n_cognome); k++) {
                chiave[k] = (char) toupper(chiave[k]);
            }
            if (strncmp(key, chiave, ls) == 0) {
                printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                       v[i].codice, v[i].nome, v[i].cognome, v[i].data, v[i].categoria,
                       v[i].ore_allenamento);
            } else {
                finito = 1;
            }

        }
        finito = 0;
        for (i = j - 1; i >= 0 && finito == 0; i--) {
            strcpy(chiave, v[i].cognome);
            for (k = 0; k <= (v[i].n_cognome); k++) {
                chiave[k] = (char) toupper(chiave[k]);
            }
            if (strncmp(key, chiave, ls) == 0) {
                printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                       v[i].codice, v[i].nome, v[i].cognome, v[i].data, v[i].categoria,
                       v[i].ore_allenamento);
            } else {
                finito = 1;
            }

        }
    }
}
