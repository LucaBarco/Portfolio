//
// Created by Luca Barco on 20/12/2017.
//

#include "PQ.h"
#include <stdlib.h>
struct heap{
    Item *A;
    int heapsize;
};

//funzione init
Heap HEAPinit(int MAXN){
    Heap x=malloc(sizeof(*x));
    x->A=malloc(MAXN*sizeof(Item));
    x->heapsize=0;
    return x;
}

//funzioni per ottenere indici di padre e figli
int LEFT(int i){
    return (i*2+1);
}
int RIGHT(int i){
    return (i*2+2);
}
int PARENT(int i){
    return ((i-1)/2);
}

//funzione di lettura da file
Heap leggiFile(FILE *fp,Heap h){
    Item temp=ItemScan(fp);
    while(ItemEq(temp,ItemSetVoid())!=1){
        HeapFill(h,temp);
        h->heapsize=h->heapsize+1;
        temp=ItemScan(fp);
    }
    HEAPbuild(h);
    return h;
}

void HeapFill(Heap h,Item x){
    int i;
    i=h->heapsize;
    h->A[i]=x;
    return;
}

//funzione di scrittura
void HeapDisplay(FILE *fp,Heap h){
    int i;
    for(i=0;i<h->heapsize;i++){
        ItemShow(fp,h->A[i]);
    }
}
//funzione di Heapify
void HEAPify(Heap h,int i){
    int l,r,largest;
    l=LEFT(i);
    r=RIGHT(i);
    if((l<h->heapsize)&& (ItemLess(h->A[l],h->A[i])))
        largest=l;
    else
        largest=i;
    if((r<h->heapsize)&&(ItemLess(h->A[r],h->A[largest])))
        largest=r;
    if(largest!=i){
        Swap(h,i,largest);
        HEAPify(h,largest);
    }
    return;
}
void Swap(Heap h,int i,int l){
    Item temp;
    temp=h->A[i];
    h->A[i]=h->A[l];
    h->A[l]=temp;

    return;
}
//costruzione albero partendo dal vettore
void HEAPbuild(Heap h){
    int i;
    for(i=(h->heapsize)/2-1;i>=0;i--)
        HEAPify(h,i);
    return;
}
//funzione di INSERT
void HeapInsert(Heap pq,Item x){
    int i;
    i=pq->heapsize++;
    while((i>=1)&&(ItemGreater(pq->A[PARENT(i)],x))){
        pq->A[i]=pq->A[PARENT(i)];
        i=(i-1)/2;
    }
    pq->A[i]=x;
    return;
}

//funzione di Change
void PQchange(Heap h,int pos,Item x){
    while((pos>=1)&&(ItemLess(h->A[PARENT(pos)],x))){
        h->A[pos]=h->A[PARENT(pos)];
        pos=(pos-1)/2;
    }
    h->A[pos]=x;
    HEAPify(h,pos);
    return;
}

//funzione di Delete
void HeapDelete(Heap h,Item x){
    int i=h->heapsize;int j;
    for(i=h->heapsize;i>=1 && ItemEq(h->A[i],x)!=1;i=(i-1)/2){
        h->A[i]=h->A[PARENT(i)];
    }
    h->A[i]=ItemSetVoid();

    Swap(h,i,h->heapsize);
    h->heapsize--;
    HEAPbuild(h);
}

//funzione di estrazione del minimo
Item PQextractMin(Heap pq){
    Item min;
    Swap(pq,0,pq->heapsize-1);
    min=pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq,0);
    return min;
}
//lettura campi
int HeapSize(Heap h){
    return h->heapsize;
}