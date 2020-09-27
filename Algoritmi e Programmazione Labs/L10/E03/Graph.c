//
// Created by Luca Barco on 08/01/2018.
//

#include "Graph.h"
#include "ST.h"
#include <stdlib.h>
#include <string.h>
#define MAX 32

typedef struct node *link;
struct node{
    int v;
    int wt;
    link next;
};

struct graph {
    int V;
    int E;
    link *adj;
    int **MatrAdj;
    ST tab;
    int *vertInST;
    link z;
};

link NEW(int v,int wt,link next){
    link p=malloc(sizeof(*p));
    p->v=v;
    p->wt=wt;
    p->next=next;
    return p;
}

Graph GRAPHinit(int N){
    //creo grafo come lista delle adiacenze
    int i;
    Graph G=malloc(sizeof(*G));
    G->E=0;
    G->V=N;
    G->z=NEW(-1,0,NULL);
    G->adj=malloc((N)*sizeof(struct node));
    for(i=0;i<N;i++){
        G->adj[i]=G->z;
    }
    G->vertInST=calloc(N,sizeof(int));
    G->tab=STinit(N);
    return G;
}

void GRAPHinsert(Graph G,Edge e){
    int v=e.v,w=e.w,wt=e.wt;
    G->adj[v]=NEW(w,wt,G->adj[v]);
    G->adj[w]=NEW(v,wt,G->adj[w]);
    G->E++;
}

Graph GRAPHread(FILE *fp,Graph G) {
    int peso, v, w;
    char s1[MAX], s2[MAX];

    if(fp==NULL){
        printf("Errore apertura file!\n");
        return NULL;
    }

    //STprint(G->tab);

    while(fscanf(fp,"%s %s %d",s1,s2,&peso)!=EOF){
        printf("Arco: %s -> %s,peso:%d\n",s1,s2,peso);
        v=STsearch(G->tab,s1);
        w=STsearch(G->tab,s2);
        printf("Arco: %d -> %d\n",v,w);
        if(v==-1||w==-1){
            printf("Errore nella ricerca nella ST di %s!\n",s1);
            continue;
        }
        else {
            int i,k,j,finito1=0,finito2=0;
            for(j=0;j<G->V && (finito1==0||finito2==0);j++){
                if(G->vertInST[j]==v && finito1==0) {
                    i = j;
                    finito1=1;
                }
                if(G->vertInST[j]==w&&finito2==0) {
                    k = j;
                    finito2=1;
                }
            }

            GRAPHinsert(G, EDGEcreate(i,k,peso));
        }
    }
return G;
}

void GRAPHprintNode(Graph G){
    printf("Numero di elaboratori:%d\n",G->V);
    int i=0;
    for(i=0;i<G->V;i++){
        printf("%s\n",STretrieveNome(G->tab,G->vertInST[i]));
    }
}

void GRAPHprintEdge(Graph G,char *key){
    //stampa
    int j=STsearch(G->tab,key);
    int c=0;
    int i=-1,k,finito=0;
    for(k=0;k<G->V && finito==0;k++){
        if(G->vertInST[k]==j){
            i=k;
            finito=1;
        }
    }
    if(i!=-1) {
        link t;
        printf("Elaboratori connessi a %s:\n", key);
        for (t = G->adj[i]; t != G->z; t = t->next) {
                printf("Elaboratore:%s \tRete di appartenza:%s\n", STretrieveNome(G->tab, G->vertInST[t->v]),
                       STretrieveRete(G->tab, G->vertInST[t->v]));
                c++;
        }
        printf("Numero di archi:%d\n",c);
        return;
    }
    printf("Errore! Nodo non trovato!\n");
}

Graph GRAPHmatr(Graph G){
    int i,j;
    link t;
    //preparo la matrice delle adiacenze
    G->MatrAdj=malloc(G->V*sizeof(int *));
    for(i=0;i<G->V;i++) {
        G->MatrAdj[i] = malloc(G->V * sizeof(int));
        for(j=0;j<G->V;j++)
            G->MatrAdj[i][j]=0;

    }

    //COMPILAZIONE DELLA MATRICE DELLE ADIACENZE
    for(i=0;i<G->V;i++){
        for(t=G->adj[i];t!=G->z;t=t->next){
            G->MatrAdj[i][t->v]=t->wt;

        }
    }
    //stampa matrice
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            printf("%d ",G->MatrAdj[i][j]);
        }
        printf("\n");
    }
    return G;
}
void calcolaFlussi(Graph G){
    int intra=0,extra=0;
    int i,j;
    link t;

    //VERSIONE CON LISTA DELLE ADIACENZE
    for(i=0;i<G->V;i++){
        for(t=G->adj[i];t!=G->z;t=t->next){
            if (strcmp(STretrieveRete(G->tab, G->vertInST[i]), STretrieveRete(G->tab, G->vertInST[t->v])) == 0) {
                //sono flussi intra-rete
                intra += t->wt;
            }
            else{
                //sono flussi inter-rete
                extra+=t->wt;
            }
        }
    }

    printf("| Flusso intra-rete: %d \t| Flusso inter-rete:%d\n",intra/2,extra/2);//divido per due perchè ho contato due volte gli archi dato che il grafo non è orientato
}

void GraphSTinsert(Graph G,char *s1,char *s2){
    int i=0;
    while(G->vertInST[i]!=0){
        i++;
    }
     G->vertInST[i]=STinsert(G->tab,s1,s2);
}
void GraphSTread(FILE *fp,Graph G){
    int i=0;
    char elab[MAX],rete[MAX];
    while(i<G->V){
        fscanf(fp,"%s %s",elab,rete);
        //printf("\triga %s %s\n\n",elab,rete);
        GraphSTinsert(G,elab,rete);
        i++;
    }
}