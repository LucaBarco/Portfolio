//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E04_ESLIST_H
#define E04_ESLIST_H


#include "esArray.h"
typedef struct eserPiano_s eserPiano_t,*link_piano;

link_piano newPointPiano();
link_piano eserScanPiano(FILE *fp);
link_piano newEser(char *nomees,int set,int rip,tabEser vett);
link_piano associaEser(link_piano t,tabEser esercizi);
link_piano nuovoNodo_piano(link_piano next,link_piano val);
link_piano InserimentoCoda_piano(link_piano h,link_piano *t,link_piano val);
link_piano nextEser(link_piano t);
void stampaEserPiano(link_piano t,FILE *fp);
char *getEserPianoNome(link_piano t,tabEser vett);
link_piano rimuoviEserNodo(link_piano h,char *k);
link_piano modificaEs(link_piano h,char *nomees_chiave,int n_rip,int n_set,tabEser vett);
int estraiRip(link_piano i);
int estraiSet(link_piano i);
link_piano eserPianoVoid();
#endif //E04_ESLIST_H
