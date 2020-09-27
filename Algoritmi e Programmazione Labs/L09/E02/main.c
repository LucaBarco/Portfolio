#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "PQ.h"
#define MAXN 20
typedef enum{
    stampa_classifica,
    nuovo_giocatore,
    elimina_giocatore,
    evoluzione,
    carica_classicifa,
    salva_classifica,
    fine
}comando;

comando leggiComando();

int main() {
    srand((unsigned int)time(NULL));
    Heap classifica=HEAPinit(MAXN);
    FILE *fp;
    int ris1,ris2;
    char nomefile[MAXN];
    comando cmd;
    Item temp,gioc1,gioc2;
    cmd=leggiComando();
    while(cmd!=fine) {
        switch (cmd) {
            case stampa_classifica:
                HeapDisplay(stdout,classifica);
                break;
            case nuovo_giocatore:
                if(HeapSize(classifica)<MAXN-2) {
                    temp = ItemScan(stdin);
                    HeapInsert(classifica, temp);
                }
                else{
                    printf("----------> Massimo numero di giocatori raggiunto!\n");
                }
                break;
            case elimina_giocatore:
                temp=ItemScan(stdin);
                HeapDelete(classifica,temp);
                break;
            case evoluzione:
                gioc1=PQextractMin(classifica);
                gioc2=PQextractMin(classifica);
                printf("Sfida: \t %s VS %s\n",ItemKeyGet(gioc1),ItemKeyGet(gioc2));
                ris1=rand() < RAND_MAX/2;
                ris2=rand() < RAND_MAX/2;
                if(ris1>ris2){
                    //vincitore è gioc1;
                    printf("\t VITTORIA DI %s !\n",ItemKeyGet(gioc1));
                    aggiornaPunti(gioc1,gioc2,1);
                }
                else{
                    //vincitore è gioc2
                    printf("\t VITTORIA DI %s !\n",ItemKeyGet(gioc2));
                    aggiornaPunti(gioc1,gioc2,2);
                }
                if(ItemGetPunti(gioc1)<=0){
                    printf("%s ELIMINATO!\n",ItemKeyGet(gioc1));
                    HeapDelete(classifica,gioc1);
                    HeapInsert(classifica,gioc2);
                }
                else if(ItemGetPunti(gioc2)<=0){
                    printf("%s ELIMINATO!\n",ItemKeyGet(gioc2));
                    HeapDelete(classifica,gioc2);
                    HeapInsert(classifica,gioc1);
                }
                else{
                    HeapInsert(classifica,gioc1);
                    HeapInsert(classifica,gioc2);
                }
                break;
            case carica_classicifa:
                printf("Inserisci nome file:");
                scanf("%s",nomefile);
                fp=fopen(nomefile,"r");
                if(fp!=NULL) {
                    classifica = leggiFile(fp, classifica);
                }
                else{
                    printf("Errore durante l'apertura di %s\n",nomefile);
                }
                fclose(fp);
                break;
            case salva_classifica:
                printf("Inserisci nome file:");
                scanf("%s",nomefile);
                fp=fopen(nomefile,"w");
                if(fp!=NULL) {
                    HeapDisplay(fp,classifica);
                }
                else{
                    printf("Errore durante l'apertura di %s\n",nomefile);
                }
                fclose(fp);
                break;

            default:
                printf("Comando errato!\n");
                break;
        }
        cmd = leggiComando();
    }
    return 0;
}

comando leggiComando(){
    int n=7;
    char m[7][20]={"stampa_classifica","nuovo_giocatore","elimina_giocatore",
                   "evoluzione","carica_classifica","salva_classifica","fine"};
    int i=0;
    char cmd[20];
    printf("--------------- MENU ---------------\n"
                   "\t- stampa_classifica : stampa la classifica\n"
                   "\t- nuovo_giocatore : aggiungi giocatore al torneo\n"
                   "\t- elimina_giocatore : elimina giocatore dal torneo\n"
                   "\t- evoluzione : procedi con il torneo\n"
                   "\t- carica_classifica : carica una classifica iniziale da file\n"
                   "\t- salva_classifica : salva la classifica su file\n"
                   "\t- fine\nComando: ");
    scanf("%s",cmd);
    while(i<7&&strcmp(cmd,m[i])!=0){
        i++;
    }
    return i;
}