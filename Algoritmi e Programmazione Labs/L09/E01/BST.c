//
// Created by Luca Barco on 19/12/2017.
//

#include "BST.h"

typedef struct BST_node *link;
struct BST_node{
    Item item;
    link r;
    link l;

    int liv;
};
struct binarysearchtree{
    link root;
    link z;

};
//funzione crezione nodo
link NEW(Item item,link l,link r,int liv){
    link x=malloc(sizeof(*x));
    x->item=item;
    x->r=r;
    x->l=l;

    x->liv=liv;
    return x;
}
//funzione creazione albero
BST BSTInit(){
    BST bst=malloc(sizeof(*bst));
    bst->root=(bst->z=NEW(ITEMsetVoid(),NULL,NULL,0));
    return bst;
}
//funzione lettura da file

link BSTreadPreorder_R(FILE *fp,link h,link z,int *finito){
    Item temp;
    int dx,sx;
    temp=ITEMscan(fp,&dx,&sx);
    if(ITEMequal(temp,ITEMsetVoid())==0){
        *finito=1;
        return h;
    }
    if(h==z && *finito==0){
       h= NEW(temp,z,z,0);
    }
    if(sx==1&&*finito==0){
        h->l=BSTreadPreorder_R(fp,h->l,z,finito);
    }
    if(dx==1&&*finito==0){
        h->r=BSTreadPreorder_R(fp,h->r,z,finito);
    }
    return h;
}
//wrapper
BST BSTreadPreorder(FILE *fp){
    BST bst=BSTInit();
    int finito=0;
    bst->root=BSTreadPreorder_R(fp,bst->root,bst->z,&finito);
    return bst;
}

//funzione scrittura su file
void BSTwritePreorder_R(FILE *fp,link h,link z,int l){
    int i;
    if(h==z){
        return;
    }
    for(i=0;i<l;i++){
        fprintf(fp,"\t");
    }
    ITEMprint(fp,h->item);
    BSTwritePreorder_R(fp,h->l,z,l+1);
    BSTwritePreorder_R(fp,h->r,z,l+1);
    return;
}
//wrapper
void BSTwritePreorder(FILE *fp,BST bst){
    int l=0;
    BSTwritePreorder_R(fp,bst->root,bst->z,l);
}
//funzione conta nodi completi tra livelli L1 e L2

int BSTcount_R(link h,link z,int L1,int L2,int cont,int lev){
    if(h==z){
        return cont;
    }

    if(lev>=L2){
        return cont;
    }
    if(lev>=L1 && lev<L2 && h->l!=z && h->r!=z){
        cont++;
    }
    BSTcount_R(h->l,z,L1,L2,cont,lev+1);
    BSTcount_R(h->r,z,L1,L2,cont,lev+1);
}
//wrapper
int BSTcount(BST bst,int L1,int L2){
    return BSTcount_R(bst->root,bst->z,L1,L2,0,0);
}
//funzione conta archi tra due nodi

int BSTdistance_R(link h,link z,char *k1,char *k2,int count,int *inizio,int *exit){
    int temp;
    if(h==z){
        return count;
    }
    if(*exit==1){
        return count;
    }
    if(strcmp(k1,KEYget(h->item))==0){
        *inizio=1;
    }
    else if(strcmp(k2,KEYget(h->item))==0){
        *exit=1;
        return count;
    }
    if(*inizio==1 && *exit==0){
        count=count+1;
    }
    temp= BSTdistance_R(h->l,z,k1,k2,count,inizio,exit);
    if(*exit==0) {

        temp = BSTdistance_R(h->r, z, k1, k2, count, inizio, exit);
    }
    count=temp;
    return count;
}
//wrapper
int BSTdistance(BST bst,char *k1,char *k2){
    int inizio=0,exit=0;
    return BSTdistance_R(bst->root,bst->z,k1,k2,0,&inizio,&exit);
}
//funzione di inversione ordine

void BSTmirror_R(link h,link z){
    link temp1,temp2;
    if(h==z){
        return;
    }
    BSTmirror_R(h->r,z);
    BSTmirror_R(h->l,z);
    temp1=h->l;
    temp2=h->r;
    h->r=temp1;
    h->l=temp2;

}
//wrapper
void BSTmirror(BST bst){
    BSTmirror_R(bst->root,bst->z);
}
//funzione distruzione albero

void BSTfree_R(link h,link z){
    if(h==z){
        return;
    }
    BSTfree_R(h->l,z);
    BSTfree_R(h->r,z);
    free(h->l);
    free(h->r);
    free(h);
    return;
}
//wrapper
void BSTfree(BST bst){
    BSTfree_R(bst->root,bst->z);
}