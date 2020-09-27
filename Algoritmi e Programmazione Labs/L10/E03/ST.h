//
// Created by Luca Barco on 08/01/2018.
//

#ifndef E03_ST_H
#define E03_ST_H

typedef struct st *ST;

ST STinit(int M);
static int hash(char *v,int M);
int full(ST st,int j);
int STinsert(ST st,char *id1,char *id2);
int STsearch(ST st,char *k);
char * STretrieveNome(ST st,int i);
char * STretrieveRete(ST st,int i);
void STprint(ST st);
#endif //E03_ST_H
