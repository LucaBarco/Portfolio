//
// Created by Luca Barco on 20/12/2017.
//

#ifndef E02_PQ_H
#define E02_PQ_H
#include "Item.h"
typedef struct heap *Heap;

//funzione init
Heap HEAPinit(int MAXN);

//funzioni per ottenere indici di padre e figli
int LEFT(int i);
int RIGHT(int i);
int PARENT(int i);

//leggiFile
Heap leggiFile(FILE *fp,Heap h);
void HeapFill(Heap h,Item x);
//funzione di scrittura
void HeapDisplay(FILE *fp,Heap h);

//funzione di Heapify
void HEAPify(Heap h,int i);
void Swap(Heap h,int i,int l);

//costruzione albero partendo dal vettore
void HEAPbuild(Heap h);

//funzione di INSERT
void HeapInsert(Heap pq,Item x);

//funzione di Change
void PQchange(Heap h,int pos,Item x);

//funzione di Delete
void HeapDelete(Heap h,Item x);

//estrazione minimo
Item PQextractMin(Heap pq);

//lettura campi
int HeapSize(Heap h);
#endif //E02_PQ_H
