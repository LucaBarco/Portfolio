#include <stdio.h>
#include <string.h>
#include "Graph.h"
#ifndef MAX
#define MAX 30
#endif
typedef enum{
    stampa_vertici,
    stampa_archi,
    genera_matrice,
    stampa_flusso,
    fine,
}comando;

comando leggiComando();

int main(int argc,char **argv) {
    Graph G;
    FILE *fp;
    comando cmd;
    int i=0,N_vertici;
    char vertice[MAX];
    char elab[MAX],rete[MAX];

    fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return -1;
    }
    fscanf(fp,"%d",&N_vertici);
    G=GRAPHinit(N_vertici);
    GraphSTread(fp,G);
    G=GRAPHread(fp,G);
    fclose(fp);

    cmd=leggiComando();

    while(cmd!=fine){
        switch(cmd){
            case stampa_vertici:
                GRAPHprintNode(G);
                break;

            case stampa_archi:
                printf("Nome del verice: ");
                scanf("%s",vertice);
                GRAPHprintEdge(G,vertice);
                break;

            case genera_matrice:
                GRAPHmatr(G);
                break;

            case stampa_flusso:
                calcolaFlussi(G);
                break;

            default:
                printf("Comando errato!\n");
                break;
        }
        cmd=leggiComando();
    }
    return 0;
}

comando leggiComando(){
    int i=0;
    char matr[5][15]={"stampa_vertici",
                      "stampa_archi",
                      "genera_matrice",
                      "stampa_flusso",
                      "fine"};
    char nome[15];
    printf("--------------- MENU ---------------\n"
                   "\t- stampa_vertici : stampa numero vertici e li elenca\n"
                   "\t- stampa_archi : stampa numero di archi incidenti su un nodo ed elenco a cui essi sono connessi\n"
                   "\t- genera_matrice : genera matrice delle adiacenze partendo dalla lista \n"
                   "\t- stampa_flusso : stampa ammontare del flusso intra- ed inter-rete\n"
                   "\t- fine\n"
                   "Inserire comando: ");
    scanf("%s",nome);
    while(i<5 && strcmp(nome,matr[i])!=0)
        i++;

    return i;
}