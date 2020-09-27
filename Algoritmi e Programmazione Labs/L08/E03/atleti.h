//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E03_ATLETI_H
#define E03_ATLETI_H
#include "esercizi.h"
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
link_atleta leggiFile_atleta(tabAtleti *atleti);
link_atleta nuovoNodo(link_atleta next,atleta val);
link_atleta InserimentoCoda(tabAtleti *atleti,atleta val);
link_atleta rimuoviNodo(link_atleta h,char *k);//in base a chiave k
link_atleta ricercaCodice(tabAtleti *atleti,char *chiave);
link_atleta ricercaCognome(tabAtleti *atleti,char *chiave);
link_atleta aggiungiAtleta(tabAtleti *atleti);
link_atleta cancellaAtleta(tabAtleti *atleti);
void stampaAtleta(tabAtleti *atleti,char *chiave);
void aggiornaOre(tabAtleti *atleti);
link_atleta trovaCodice(tabAtleti *atleti,char *cognome,char *nome);
link_atleta leggiFile_piano(link_atleta h,char *codice,tabEser *vett,link_atleta i);
link_piano nuovoNodo_piano(link_piano next,eserPiano_t val);
link_piano InserimentoCoda_piano(link_piano h,link_piano *t,eserPiano_t val);
link_piano modifica_eser(link_atleta h,char *cognome,char *nome,char *nomees,tabEser *esercizi);
link_piano rimuoviEser(link_atleta i,char *k);

#endif //E03_ATLETI_H
