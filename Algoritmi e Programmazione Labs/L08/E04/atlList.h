//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E04_ATLLIST_H
#define E04_ATLLIST_H
#include "atl.h"
#include "esList.h"
#include "esArray.h"
typedef struct tabAtleti_s *tabAtleti;
typedef struct nodo_s *link_atleta;


tabAtleti nuovaTabAt();
tabAtleti leggiFile_atleta(tabAtleti atleti);
link_atleta nuovoNodo(link_atleta next,atleta val);
link_atleta InserimentoCoda(tabAtleti atleti,atleta val);
tabAtleti rimuoviNodo(tabAtleti atleti,char *k);//in base a chiave k
link_atleta ricercaCodice(tabAtleti atleti,char *chiave);
link_atleta ricercaCognome(tabAtleti atleti,char *chiave);
tabAtleti aggiungiAtleta(tabAtleti atleti);
tabAtleti cancellaAtleta(tabAtleti atleti);
void stampaAtleta(tabAtleti atleti,char *chiave);
void aggiornaOre(tabAtleti atleti);
link_atleta trovaCodice(tabAtleti atleti,char *cognome,char *nome);
tabAtleti leggiFile_piano(tabAtleti atleti,char *codice,tabEser vett);
tabAtleti rimuoviEser(tabAtleti atleti,char *codice,char *k);
tabAtleti nuovoEser(tabAtleti atleti,char *codice,char *nomees,int set,int rip,tabEser vett);
tabAtleti modificaEsAtl(tabAtleti atleti,char *codice_chiave, char *nomees_chiave,int n_set,int n_rip,tabEser vett);
atleta extractVal(link_atleta i);
int extractRip(link_atleta i,char *nomees,tabEser vett);
int extractSet(link_atleta i,char *nomees,tabEser vett);
char *extractCode(link_atleta i);

#endif //E04_ATLLIST_H
