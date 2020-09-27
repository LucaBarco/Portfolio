//
// Created by Luca Barco on 17/01/2018.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H
#include "Edge.h"
#include <stdio.h>

typedef struct graph *Graph;

Graph GRAPHinit(int N);
Graph GRAPHread(FILE *fp,Graph G);
void GRAPHinsert(Graph G,Edge e);
int GraphCount(Graph G);
Graph GRAPHmatr(Graph G);
void GraphSTinsert(Graph G,char *s1);
void GraphSTread(FILE *fp,Graph G);
char *GRAPHstRetrieve(Graph G,int i);
int **GRAPHminDist(Graph G);
int **GraphCamMinBF(Graph G,int **matr,int s);
int *GRAPHdfs(Graph G,int *n,int tipo);
void cancellaVertici(Graph G,int *sol,int k);
void GraphResume(Graph G,int *sol,int k);
int isAciclico(Graph G);
int *GRAPHcc(Graph G,int *ncc);
void GRAPHresumeArchi(Graph G,int *sol,int n);
int GRAPHmstP(Graph G);
void GraphPrint(Graph G);
void GRAPHremove(Graph G,Edge e);
#endif //E01_GRAPH_H
