//
// Created by Luca Barco on 13/01/2018.
//

#include "BST.h"
#include <stdlib.h>
typedef struct BSTnode *link;
struct BSTnode{
    Item item;
    link l;
    link r;
};
struct binarysearchtree{
    link radice;
    int N;
    link z;
};
link NEW(Item item,link l,link r){
    link x=malloc(sizeof(*x));
    x->item=item;
    x->l=l;
    x->r=r;
    return x;
}
BST Bstinit(){
    BST bst=malloc(sizeof(*bst));
    bst->N=0;
    bst->radice=(bst->z=NEW(ItemSetVoid(),NULL,NULL));
    return bst;
}
link insertR(link h,Item x,link z){
    if(ItemEq(h->item,z->item)) {
        return NEW(x, z, z);
    }
    if(ItemLess(x,h->item)==1){
            h->l=insertR(h->l,x,z);
    }
    else{
        h->r=insertR(h->r,x,z);
    }
    return h;

}
void BSTinsert_leaf(BST bst,Item item){
    bst->radice=insertR(bst->radice,item,bst->z);
    bst->N++;
    return;
}
Item SearchR(link h,Item item,link z){
    if(ItemEq(h->item,z->item)){
        return ItemSetVoid();
    }
    if(ItemEq(item,h->item)==1){
        return h->item;
    }
    if(ItemLess(item,h->item)==1){
        return SearchR(h->l,item,z);
    }
    else{
        return SearchR(h->r,item,z);
    }
}
Item BSTsearch(BST bst,Item item){
    return SearchR(bst->radice,item,bst->z);
}
void BSTfree(BST bst);