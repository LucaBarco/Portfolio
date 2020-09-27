#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atlList.h"
#define MAXC 26
#define MAXN 51
typedef enum{
    stampa_atleta,
    aggiorna_ore,
    ricerca_codice,
    ricerca_cognome,
    aggiunta_atleta,
    cancella_atleta,
    carica_piano,
    modifica_esercizio,
    stampa_esercizio,
    fine
}comando;
comando leggiComando();

//non funzionano:

//modifica esercizio

int main() {
    link_atleta i;
    char cognome_chiave[MAXC],nome_chiave[MAXC],esercizio_chiave[MAXN],codice_chiave[6];
    int k,scelta,set,rip;
    tabEser esercizi=nuovaTabEs();
    tabAtleti atleti=nuovaTabAt();
    comando cmd;
    link_piano j;

    atleti=leggiFile_atleta(atleti);
    if(atleti==NULL){
        return -1;
    }
    esercizi=leggiFile_es(esercizi);
    if(esercizi==NULL){
        return -1;
    }
    //DEBUG!
    //stampaTuttiEser(esercizi);
    //
    cmd=leggiComando();
    while(cmd!=fine){
        switch (cmd){
            case stampa_atleta:
                printf("Inserire il codice dell'atleta di cui stampare i dettagli: ");
                scanf("%s",codice_chiave);
                stampaAtleta(atleti,codice_chiave);
                break;

            case aggiorna_ore:
                aggiornaOre(atleti);
                break;
            case ricerca_cognome:
                printf("Inserire il cognome da cercare (anche parziale): ");
                scanf("%s",cognome_chiave);
                ricercaCognome(atleti,cognome_chiave);
                break;

            case ricerca_codice:
                printf("Inserire il codice da cercare: ");
                scanf("%s",codice_chiave);
                i=ricercaCodice(atleti,codice_chiave);
                if(i==NULL){
                    printf("------------Nessuna corrispondenza trovata!------------\n");
                }
                else{
                    atletaPrint(extractVal(i),stdout);
                }
                break;

            case aggiunta_atleta:
                atleti=aggiungiAtleta(atleti);
                break;

            case cancella_atleta:
                atleti=cancellaAtleta(atleti);
                break;

            case carica_piano:
                printf("Inserisci il codice dell'atleta di cui caricare il piano:");
                scanf("%s",codice_chiave);
                atleti=leggiFile_piano(atleti,codice_chiave,esercizi);
                break;

            case modifica_esercizio:
                printf("Inserisci il nome dell'atleta (nome - cognome): ");
                scanf("%s %s",nome_chiave,cognome_chiave);
                printf("%s %s\n",nome_chiave,cognome_chiave);
                i=trovaCodice(atleti,cognome_chiave,nome_chiave);
                if(i!=NULL) {
                    printf("Inserisci il nome dell'esercizio da modificare/aggiungere/togliere: ");
                    scanf("%s", esercizio_chiave);

                    printf("Vuoi :\n\t1-Modificare numero di set\n\t2-Modificare numero di ripetizioni\n\t3-Aggiungere esercizio\n\t4-Rimuovere esercizio\n(Inserisci un numero 1->4):");
                    scanf("%d", &scelta);

                    if (scelta == 1) {
                        printf("Numero di set: ");
                        scanf("%d", &set);
                        rip = extractRip(i, esercizio_chiave,esercizi);
                        //printf("%d\n",rip);
                        atleti = modificaEsAtl(atleti, codice_chiave, esercizio_chiave, set, rip,esercizi);
                    }
                    if (scelta == 2) {
                        printf("Numero di ripetizioni:");
                        scanf("%d", &rip);
                        set = extractSet(i, esercizio_chiave,esercizi);
                        //printf("%d\n",set);
                        atleti = modificaEsAtl(atleti, codice_chiave, esercizio_chiave, set, rip,esercizi);
                    }
                    if (scelta == 3) {
                        //funzione aggiunta esercizio
                        printf("Numero di set: ");
                        scanf("%d", &set);
                        printf("Numero di ripetizioni:");
                        scanf("%d", &rip);
                        atleti = nuovoEser(atleti, extractCode(i), esercizio_chiave, set, rip, esercizi);
                    }
                    if (scelta == 4) {
                        atleti = rimuoviEser(atleti, extractCode(i), esercizio_chiave);
                    }
                }

                break;
            case stampa_esercizio:
                printf("Nome dell'esercizio da ricercare: ");
                scanf("%s",esercizio_chiave);
                stampaEser(esercizi,esercizio_chiave);
                break;

            default:
                printf("Comando non valido!\n");
                break;
        }
        cmd=leggiComando();
    }
    return 0;
}
comando leggiComando(){
    int i=0;
    char temp[20];
    char comandi[10][20]={"stampa_atleta","aggiorna_ore","ricerca_codice","ricerca_cognome","aggiunta_atleta","cancella_atleta","carica_piano","modifica_esercizio","stampa_esercizio","fine"};
    printf("---------- MENU ----------\n"
                   "\t-stampa_atleta : stampa i dettagli di un atleta\n"
                   "\t-aggiorna_ore : aggiorna il monte ore settimanali di un atleta\n"
                   "\t-ricerca_codice : ricerca di un atleta per codice\n"
                   "\t-ricerca_cognome : ricerca di atleti per cognome (anche parziale)\n"
                   "\t-aggiunta_atleta : aggiungi un atleta\n"
                   "\t-cancella_atleta : cancella un atleta dato il codice\n"
                   "\t-carica_piano : carica il piano di allenamenti di un atleta\n"
                   "\t-modifica_esercizio : modifica del numero di set/ripetizioni di un esercizio del piano di un atleta\n"
                   "\t-stampa_esercizio : stampa i dettagli di un esercizio\n"
                   "\t-fine\n");
    scanf("%s",temp);
    while(strcmp(temp,comandi[i])!=0 && i<=9){
        i++;
    }
    return i;
}