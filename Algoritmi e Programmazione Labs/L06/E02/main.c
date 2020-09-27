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
void ordinamento( atleta *v,int n,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria);
void MergeSort(atleta *v,int l,int r,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria,atleta **ordine_nascita_t,atleta **ordine_codice_t,atleta **ordine_cognome_t,atleta **ordine_categoria_t);
void Merge(atleta *v,int l,int q,int r,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria,atleta **ordine_nascita_t,atleta **ordine_codice_t,atleta **ordine_cognome_t,atleta **ordine_categoria_t);
int confrontaChiave(comando cmd, atleta **v,int i,int j);
void aggiornaOre(atleta *elenco,int n,atleta **ordine_codice);
int ricercaDicotomica(comando cmd,char *key, atleta **v, int n);
void stampaCategoria(atleta **v,int n);
char* aggiustaData(struct data_s nascita1);
void ricercaNuoveOccorrenze(int j,char *chiave,atleta **v,int n);

int main() {

    FILE*fp;
    atleta *elenco,**ordine_nascita,**ordine_codice,**ordine_cognome, **ordine_categoria;
    int n_atleti;
    comando cmd;
    int tipo_stampa; //1 se su file, 2 se su schermo
    char codice_chiave[6];
    char cognome_chiave[MAXC];
    int j;

    elenco=leggiFile(fp,elenco,&n_atleti);

    if((n_atleti)==-1){
        return 0;
    }

    ordine_nascita=(atleta **)malloc(n_atleti*sizeof(atleta *));
    printf("1\n");
    ordine_codice=(atleta **)malloc(n_atleti*sizeof(atleta *));
    printf("2\n");
    ordine_cognome=(atleta **)malloc(n_atleti*sizeof(atleta *));
    ordine_categoria=(atleta **)malloc(n_atleti*sizeof(atleta *));
    printf("3\n");

    for(j=0;j<n_atleti;j++){
        ordine_nascita[j]=ordine_codice[j]=ordine_cognome[j]=ordine_categoria[j]=&elenco[j];
    }
    ordinamento(elenco,n_atleti,ordine_nascita,ordine_codice,ordine_cognome,ordine_categoria);
    printf("4\n");
    cmd=leggiComando();
    while(cmd!=fine) {
        switch (cmd) {
            case stampa_anagrafica:
                printf("Effettuare la stampa su: \n\t1 - file\n\t2-schermo\nInserire numero:");
                scanf("%d", &tipo_stampa);
                stampaElenco(elenco, n_atleti, tipo_stampa);
                break;

            case ordina_nascita:
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",ordine_nascita[j]->codice,ordine_nascita[j]->nome,ordine_nascita[j]->cognome,ordine_nascita[j]->data,ordine_nascita[j]->categoria,ordine_nascita[j]->ore_allenamento);
                }
                break;

            case ordina_codice:
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",ordine_codice[j]->codice,ordine_codice[j]->nome,ordine_codice[j]->cognome,ordine_codice[j]->data,ordine_codice[j]->categoria,ordine_codice[j]->ore_allenamento);
                }
                break;

            case ordina_cognome:
                for(j=0;j<n_atleti;j++){
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",ordine_cognome[j]->codice,ordine_cognome[j]->nome,ordine_cognome[j]->cognome,ordine_cognome[j]->data,ordine_cognome[j]->categoria,ordine_cognome[j]->ore_allenamento);
                }
                break;

            case stampa_categoria:
                stampaCategoria(ordine_categoria,n_atleti);
                break;

            case aggiorna_ore:
                aggiornaOre(elenco,n_atleti,ordine_codice);
                break;

            case ricerca_codice:
                printf("Inserire il codice da ricercare: ");
                scanf("%s", codice_chiave);
                j=ricercaDicotomica(cmd,codice_chiave,ordine_codice,n_atleti);

                if(j==-1){
                    printf("Atleta non trovato!\n");
                }
                else {
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
                           ordine_codice[j]->codice, ordine_codice[j]->nome, ordine_codice[j]->cognome, ordine_codice[j]->data, ordine_codice[j]->categoria,
                           ordine_codice[j]->ore_allenamento);
                }
                    break;

            case ricerca_cognome:
                printf("Inserire il cognome da ricercare (anche parziale): \n");
                scanf("%s", cognome_chiave);
                j=ricercaDicotomica(cmd,cognome_chiave,ordine_cognome,n_atleti);
                if(j==-1){
                    printf("Cognome non trovato!\n");
                }
                else {
                    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                           ordine_cognome[j]->codice, ordine_cognome[j]->nome, ordine_cognome[j]->cognome, ordine_cognome[j]->data, ordine_cognome[j]->categoria,
                           ordine_cognome[j]->ore_allenamento);
                    //ricerca di tutte le altre occorrenze
                    ricercaNuoveOccorrenze(j,cognome_chiave,ordine_cognome,n_atleti);
                }
                break;

            default:
                printf("Comando non valido!\n");

        }
        cmd=leggiComando();
    }
    free(ordine_categoria);
    free(ordine_codice);
    free(ordine_cognome);
    free(ordine_nascita);
    for(j=0;j<n_atleti;j++){
        free(elenco[j].nome);
        free(elenco[j].cognome);
        free(elenco[j].codice);
        free(elenco[j].categoria);
        free(elenco[j].data);
    }
    free(elenco);
    return 0;
}

atleta *  leggiFile(FILE *fp, atleta *v,int *n){
    //leggo il file atleti.txt e lo salvo in un vettore di struct atleti_s allocato dinamicamente
    //ritorno il numero di atleti
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
    }
    if(tipo_stampa==2) {
        fp=stdout;
    }
    for (i = 0; i < N; i++) {
            fprintf(fp,"\n\tNome:%s \tCognome:%s \tData di nascita: %s", v[i].nome, v[i].cognome, v[i].data);
        } 
        if(tipo_stampa==1){
        printf("----------Stampa su file effettuata!----------\n");
        fp=fclose(fp); 
			}
    return;
}

void ordinamento(atleta *v,int n,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria){
    //wrapper
    int l=0,r=n-1;
    atleta **ordine_nascita_t=(atleta **)malloc(n*sizeof(atleta *));
    atleta **ordine_codice_t=(atleta **)malloc(n*sizeof(atleta *));
    atleta **ordine_cognome_t=(atleta **)malloc(n*sizeof(atleta *));
    atleta **ordine_categoria_t=(atleta **)malloc(n*sizeof(atleta *));
    MergeSort(v,l,r,ordine_nascita,ordine_codice,ordine_cognome,ordine_categoria,ordine_nascita_t,ordine_codice_t,ordine_cognome_t,ordine_categoria_t); //passare per parametri anche i vettori temporanei e fare i 4 cicli for di copiatura
}

void MergeSort(atleta *v,int l,int r,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria,atleta **ordine_nascita_t,atleta **ordine_codice_t,atleta **ordine_cognome_t,atleta **ordine_categoria_t){
    int q=(r+l)/2;
    if(l>=r)
        return ;
    MergeSort(v,l,q,ordine_nascita,ordine_codice,ordine_cognome,ordine_categoria,ordine_nascita_t,ordine_codice_t,ordine_cognome_t,ordine_categoria_t);
    MergeSort(v,q+1,r,ordine_nascita,ordine_codice,ordine_cognome,ordine_categoria,ordine_nascita_t,ordine_codice_t,ordine_cognome_t,ordine_categoria_t);
    Merge(v,l,q,r,ordine_nascita,ordine_codice,ordine_cognome,ordine_categoria,ordine_nascita_t,ordine_codice_t,ordine_cognome_t,ordine_categoria_t);
}

void Merge(atleta *v,int l,int q,int r,atleta **ordine_nascita,atleta **ordine_codice,atleta **ordine_cognome,atleta **ordine_categoria,atleta **ordine_nascita_t,atleta **ordine_codice_t,atleta **ordine_cognome_t,atleta **ordine_categoria_t) {

    int i1 = l, j1 = q + 1, i2 = l, j2 = q + 1, i3 = l, j3 = q + 1, i4 = l, j4 = q + 1, k,j;
    for (k = l; k <= r; k++) {
        printf("%d\n", k);
        //ordinamento codice
        if(i1>q){
            ordine_codice_t[k]=ordine_codice[j1];
            j1++;
        }
        else if (j1>r){
            ordine_codice_t[k]=ordine_codice[i1];
            i1++;
        }
        else if(confrontaChiave(ordina_codice,ordine_codice,i1,j1)<=0){
            ordine_codice_t[k]=ordine_codice[i1];
            i1++;
        }
        else{
            ordine_codice_t[k]=ordine_codice[j1];
            j1++;
        }
        //ordinamento nascita
        if(i2>q){
            ordine_nascita_t[k]=ordine_nascita[j2];
            j2++;
        }
        else if (j2>r){
            ordine_nascita_t[k]=ordine_nascita[i2];
            i2++;
        }
        else if(confrontaChiave(ordina_nascita,ordine_nascita,i2,j2)<=0){
            ordine_nascita_t[k]=ordine_nascita[i2];
            i2++;
        }
        else{
            ordine_nascita_t[k]=ordine_nascita[j2];
            j2++;
        }
        //ordinamento cognome
        if(i3>q){
            ordine_cognome_t[k]=ordine_cognome[j3];
            j3++;
        }
        else if (j3>r){
            ordine_cognome_t[k]=ordine_cognome[i3];
            i3++;
        }
        else if(confrontaChiave(ordina_cognome,ordine_cognome,i3,j3)<=0){
            ordine_cognome_t[k]=ordine_cognome[i3];
            i3++;
        }
        else{
            ordine_cognome_t[k]=ordine_cognome[j3];
            j3++;
        }
        //ordinamento categoria
        if(i4>q){
            ordine_categoria_t[k]=ordine_categoria[j4];
            j4++;
        }
        else if (j4>r){
            ordine_categoria_t[k]=ordine_categoria[i4];
            i4++;
        }
        else if(confrontaChiave(stampa_categoria,ordine_categoria,i4,j4)<=0){
            ordine_categoria_t[k]=ordine_categoria[i4];
            i4++;
        }
        else{
            ordine_categoria_t[k]=ordine_categoria[j4];
            j4++;
        }

    }

    for(k=l;k<=r;k++){
        ordine_nascita[k]=ordine_nascita_t[k];
        ordine_codice[k]=ordine_codice_t[k];
        ordine_cognome[k]=ordine_cognome_t[k];
        ordine_categoria[k]=ordine_categoria_t[k];
    }

}

int confrontaChiave(comando cmd, atleta **v,int i,int j){

    struct data_s nascita1,nascita2;
    char *data_1,*data_2;
    char nome1[MAXC],nome2[MAXC],cognome1[MAXC],cognome2[MAXC],categoria1[MAXC],categoria2[MAXC];
    int k=0,p;
    switch (cmd){
        case ordina_nascita:
            sscanf(v[i]->data,"%d/%d/%d",&nascita1.giorno,&nascita1.mese,&nascita1.anno);
            data_1=aggiustaData(nascita1);
            sscanf(v[j]->data,"%d/%d/%d",&nascita2.giorno,&nascita2.mese,&nascita2.anno);
            data_2=aggiustaData(nascita2);
            printf("%s\t%s\n",data_1,data_2);
            return strcmp(data_1,data_2);

        case ordina_cognome:
            strcpy(cognome1,v[i]->cognome);
            strcpy(cognome2,v[j]->cognome);
            //case sensitive
            for(k=0;k<=v[i]->n_cognome;k++){
                cognome1[k]= (char) toupper(cognome1[k]);
            }

            for(k=0;k<=v[j]->n_cognome;k++){
                cognome2[k]= (char) toupper(cognome2[k]);
            }

            printf("%s %s\n",cognome1,cognome2);
            if(strcmp(cognome1,cognome2)==0) {

                strcpy(nome1, v[i]->nome);
                strcpy(nome2, v[j]->nome);
                for (k = 0; k <= v[i]->n_nome; k++) {
                    nome1[k]= (char) toupper(nome1[k]);
                }

                for (k = 0; k <= v[j]->n_nome; k++) {
                    nome2[k]= (char) toupper(nome2[k]);
                }

                return strcmp(nome1, nome2);
            }
            return strcmp(cognome1,cognome2);

        case ordina_codice:
            return(strcmp(v[i]->codice,v[j]->codice));

        case stampa_categoria:
            strcpy(categoria1,v[i]->categoria);
            strcpy(categoria2,v[j]->categoria);
            for (k = 0; k <= v[i]->n_categoria; k++) {
                categoria1[k]= (char) toupper(categoria1[k]);
            }

            for (k = 0; k <= v[j]->n_categoria; k++) {
                categoria2[k]= (char) toupper(categoria2[k]);
            }

            return strcmp(categoria1,categoria2);
        default:
            break;
    }

}

int ricercaDicotomica(comando cmd,char *key, atleta **v, int n) {
    int l = 0, r = n - 1;
    int m = l + (r - l) / 2;
    int ls = strlen(key);  //suppongo che la lunghezza della chiave sia sempre minore o uguale a quella dell'elemento con cui si va a confrontare
    int status, k;
    char cognome_temp[MAXC];
    for (k = 0; k <= ls; k++) {
        key[k] = (char) toupper(key[k]);
    }
    printf("%d %s\n", ls, key);
    switch (cmd) {
        case ricerca_cognome:
            while (l <= r) {
                //case sensitive
                strcpy(cognome_temp,v[m]->cognome);
                for (k = 0; k <= ((v[m])->n_cognome); k++) {
                    cognome_temp[k] = (char) toupper(cognome_temp[k]);
                }

                status = strncmp(key, cognome_temp, ls);
                if (status == 0) {
                    return m;
                }
                if (status > 0) {
                    l = m + 1;
                }
                if (status < 0) {
                    r = m - 1;
                }
                m = l + (r - l) / 2;
            }

            return -1;

        case ricerca_codice:
            while (l <= r) {
                //case sensitive
                status = strncmp(key, (v[m])->codice, ls);
                if (status == 0) {
                    return m;
                }
                if (status > 0) {
                    l = m + 1;
                }
                if (status < 0) {
                    r = m - 1;
                }
                m = l + (r - l) / 2;
            }
            return -1;
    }
}

void aggiornaOre(atleta *elenco,int n,atleta **ordine_codice) {
    int j;
    int nuove_ore;
    char codice_chiave[MAXC];
    printf("Inserire il codice dell'atleta di cui aggiornare il monte ore settimanali seguito dal nuovo numero di ore:\n");
    scanf("%s %d", codice_chiave, &nuove_ore);
    j = ricercaDicotomica(ricerca_codice,codice_chiave,ordine_codice, n);
    elenco[j].ore_allenamento = nuove_ore;
    printf("----------Aggiornamento riuscito!----------\n");
    printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
           elenco[j].codice, elenco[j].nome, elenco[j].cognome, elenco[j].data, elenco[j].categoria,
           elenco[j].ore_allenamento);

}
void stampaCategoria(atleta **v,int n) {

    int i = 0, k;
    char categoria_temp1[MAXC], categoria_temp2[MAXC];

    for (i = 0; i < n; i++) {
        strcpy(categoria_temp2,v[i]->categoria);
        for(k=0;k<=v[i]->n_categoria;k++){
            categoria_temp2[k]= (char) toupper(categoria_temp2[k]);
        }
        if (strcmp(categoria_temp1, categoria_temp2) == 0) {
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
                   v[i]->codice, v[i]->nome, v[i]->cognome, v[i]->data, v[i]->categoria, v[i]->ore_allenamento);
        } else {
            printf("\nCategoria: %s\n",v[i]->categoria);
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d\n",
                   v[i]->codice, v[i]->nome, v[i]->cognome, v[i]->data, v[i]->categoria, v[i]->ore_allenamento);
            strcpy(categoria_temp1, v[i]->categoria);
            for(k=0;k<=v[i]->n_categoria;k++){
                categoria_temp1[k]= (char) toupper(categoria_temp1[k]);
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
void ricercaNuoveOccorrenze(int j,char *key,atleta **v,int n){

    int i,k,ls,finito=0;
    char chiave[MAXC];
    ls=strlen(key);
    for (k = 0; k <= ls; k++) {
        key[k] = (char) toupper(key[k]);
    }
    for(i=j+1;i<n &&finito==0;i++){
        strcpy(chiave,v[i]->cognome);
        for (k = 0; k <= ((v[i])->n_cognome); k++) {
            chiave[k] = (char) toupper(chiave[k]);
        }
        if(strncmp(key,chiave,ls)==0){
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                   v[i]->codice, v[i]->nome, v[i]->cognome, v[i]->data, v[i]->categoria,
                   v[i]->ore_allenamento);
        }
        else{
            finito=1;
        }

    }
    finito=0;
    for(i=j-1;i>=0 &&finito==0;i--){
        strcpy(chiave,v[i]->cognome);
        for (k = 0; k <= ((v[i])->n_cognome); k++) {
            chiave[k] = (char) toupper(chiave[k]);
        }
        if(strncmp(key,chiave,ls)==0){
            printf("Atleta\n\tCodice: %s\n\tNome:%s \t Cognome:%s \tData di nascita:%s\n\tCategoria sportiva:%s \tOre di allenamento settimanali:%d",
                   v[i]->codice, v[i]->nome, v[i]->cognome, v[i]->data, v[i]->categoria,
                   v[i]->ore_allenamento);
        }
        else{
            finito=1;
        }

    }
}
