//
// Created by Luca Barco on 13/01/2018.
//

#ifndef E02_BST_H
#define E02_BST_H
#include "Item.h"

typedef struct binarysearchtree *BST;

BST Bstinit();
void BSTinsert_leaf(BST bst,Item item);
Item BSTsearch(BST bst,Item item);
void BSTfree(BST bst);
#endif //E02_BST_H
