//
// Created by Luca Barco on 13/01/2018.
//

#ifndef E02_ST_H
#define E02_ST_H
#include "Station.h"
typedef struct symboltable *ST;
typedef char* Key;

ST STinit(int n);
void STinsert(ST st,casella x);
char* STretrieveID(ST st,int i);
int STretrieveIndex(ST st,Key k);
int STretrievePosti(ST st,int i);
int STretrieveBici(ST st,int i);
int getSize(ST st);
void STprint(ST st);
void decreasePosti(ST st,int i);
void decreaseBici(ST st,int i);
void increasePosti(ST st,int i);
void increaseBici(ST st,int i);


#endif //E02_ST_H
