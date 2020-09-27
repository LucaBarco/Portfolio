//
// Created by Luca Barco on 19/12/2017.
//

#ifndef E01_BST_H
#define E01_BST_H
#include "Item.h"

typedef struct binarysearchtree *BST;


//funzione crezione albero
BST BSTInit();
//funzione lettura da file
BST BSTreadPreorder(FILE *fp);

//funzione scrittura su file
void BSTwritePreorder(FILE *fp,BST bst);

//funzione conta nodi completi tra livelli L1 e L2
int BSTcount(BST bst,int L1,int L2);

//funzione conta arche tra due nodi
int BSTdistance(BST bst,char *k1,char *k2);

//funzione di inversione ordine
void BSTmirror(BST bst);

//funzione distruzione albero
void BSTfree(BST bst);

#endif //E01_BST_H
