//
// Created by Luca Barco on 08/01/2018.
//

#ifndef E03_GRAPH_H
#define E03_GRAPH_H
#include "Edge.h"
#include <stdio.h>

typedef struct graph *Graph;

Graph GRAPHinit(int N);
Graph GRAPHread(FILE *fp,Graph G);
void GRAPHprintNode(Graph G);
void GRAPHprintEdge(Graph G,char *key);
void GRAPHinsert(Graph G,Edge e);
Graph GRAPHmatr(Graph G);
void calcolaFlussi(Graph G);
void GraphSTinsert(Graph G,char *s1,char *s2);
void GraphSTread(FILE *fp,Graph G);
#endif //E03_GRAPH_H
