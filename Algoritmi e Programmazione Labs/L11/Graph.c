//
// Created by Luca Barco on 17/01/2018.
//

#include "Graph.h"
#include "ST.h"
#include <stdlib.h>
#include <string.h>
#define MAX 32
#define maxWT 1000

typedef struct node *link;
struct node{
    int v;
    int wt;
    int cancellato;

    link next;
};

struct graph {
    int V;
    int E;
    int E1;
    link *adj;
    int **MatrAdj;
    ST tab;
    int *vertInST;
    int *verticiCancellati; //vettore dimensionato con il numero di vertici, indica se il vertice i è cancellato (v[i]=1) o no (v[i]=0)
    link z;
};


link NEW(int v,int wt,link next){
    link p=malloc(sizeof(*p));
    p->v=v;
    p->wt=wt;
    p->cancellato=0;
    p->next=next;
    return p;
}
link REMOVE(link head,link next){
    link t=head;
    head=next;
    free(t);
    return head;
}

Graph GRAPHinit(int N){
    //creo grafo come lista delle adiacenze
    int i;
    Graph G=malloc(sizeof(*G));
    G->E=0;
    G->E1=0;
    G->V=N;
    G->z=NEW(-1,0,NULL);
    G->adj=malloc((N)*sizeof(struct node));
    G->verticiCancellati=calloc(N,sizeof(int));
    for(i=0;i<N;i++){
        G->adj[i]=G->z;
    }
    G->vertInST=calloc(N,sizeof(int));
    G->tab=STinit(N);
    G->MatrAdj=malloc(G->V*sizeof(int *));
    for(i=0;i<G->V;i++) {
        G->MatrAdj[i] = malloc(G->V * sizeof(int));
    }
    return G;
}

void GRAPHinsert(Graph G,Edge e){
    int v=e.v,w=e.w,wt=e.wt;
    G->adj[v]=NEW(w,wt,G->adj[v]);
    G->adj[w]=NEW(v,wt,G->adj[w]);
    G->E++;
    G->E1++;
}
void GRAPHremove(Graph G,Edge e){
    int v=e.v,w=e.w;
    link next;
    if(G->adj[v]==G->z){
        next=G->z;
    }
    else{
        next=G->adj[v]->next;
    }
    G->adj[v]=REMOVE(G->adj[v],next);
    if(G->adj[w]==G->z){
        next=G->z;
    }
    else{
        next=G->adj[w]->next;
    }
    G->adj[w]=REMOVE(G->adj[w],next);
    G->E--;
    G->E1--;
}
int GraphCount(Graph G){
    return G->V;
}
Graph GRAPHread(FILE *fp,Graph G) {
    int peso, v, w;
    char s1[MAX], s2[MAX];

    if(fp==NULL){
        printf("Errore apertura file!\n");
        return NULL;
    }
    while(fscanf(fp,"%s %s %d",s1,s2,&peso)!=EOF){
        //printf("Arco: %s -> %s,peso:%d\n",s1,s2,peso);
        v=STsearch(G->tab,s1);
        w=STsearch(G->tab,s2);
        //printf("Arco: %d -> %d\n",v,w);
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
    //GraphPrint(G);
    return G;
}

Graph GRAPHmatr(Graph G){
    int i,j;
    link t;
    //preparo la matrice delle adiacenze

    for(i=0;i<G->V;i++) {
        for(j=0;j<G->V;j++)
            G->MatrAdj[i][j]=0;

    }

    //COMPILAZIONE DELLA MATRICE DELLE ADIACENZE
    for(i=0;i<G->V;i++){
        if(G->verticiCancellati[i]==0) {
            for (t = G->adj[i]; t != G->z; t = t->next) {
                if(G->verticiCancellati[t->v]==0) {
                    G->MatrAdj[i][t->v] = t->wt;
                }

            }
        }
    }
    //stampa matrice
    /*for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            printf("%d ",G->MatrAdj[i][j]);
        }
        printf("\n");
    }*/
    return G;
}


void GraphSTinsert(Graph G,char *s1){
    int i=0;
    while(G->vertInST[i]!=0){
        i++;
    }
    G->vertInST[i]=STinsert(G->tab,s1);
}
void GraphSTread(FILE *fp,Graph G){
    int i=0;
    char n1[MAX];
    while(i<G->V){
        fscanf(fp,"%s",n1);
        GraphSTinsert(G,n1);
        i++;
    }
}
char *GRAPHstRetrieve(Graph G,int i){
    return STretrieveNome(G->tab,G->vertInST[i]);
}
int **GRAPHminDist(Graph G){
    int i;
    int **matr;
    matr=malloc(G->V*sizeof(int *));
    for(i=0;i<G->V;i++){
        matr[i]=calloc(G->V,sizeof(int));
    }
    for(i=0;i<G->V;i++) {
        matr=GraphCamMinBF(G,matr,i);
    }
    return matr;
}
int **GraphCamMinBF(Graph G,int **matr,int s){
    int v,w,negcycfound;
    link t;
    int *st,*d;
    st=malloc(G->V*sizeof(int));
    d=malloc(G->V*sizeof(int));

    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        d[v] = maxWT;
    }
    d[s]=0;
    st[s]=s;
    for(w=0;w<G->V-1;w++){
        for(v=0;v<G->V;v++){
            if(d[v]<maxWT){
                for(t=G->adj[v];t!=G->z;t=t->next){
                    if(d[t->v]>d[v]+t->wt){
                        d[t->v]=d[v]+t->wt;
                        st[t->v]=v;
                    }
                }
            }
        }
    }
    negcycfound=0;
    for(v=0;v<G->V;v++){
        if(d[v]<maxWT){
            for(t=G->adj[v];t!=G->z;t=t->next){
                if(d[t->v]>d[v]+t->wt){
                    negcycfound=1;
                }
            }
        }
    }
    if(negcycfound==0){
        for(v=0;v<G->V;v++){
            matr[s][v]=d[v];
        }
    }
    free(st);
    free(d);
    return matr;
}
void dfsR(Graph G,Edge e,int *time,int *pre,int *post,int *st,Edge *archiB,int *count,int *isac){
    link t;
    int v,w=e.w,trovato=0;
    /*if(e.v!=e.w){
        printf("Arco  T %s - %s\n",STretrieveNome(G->tab,G->vertInST[e.v]),STretrieveNome(G->tab,G->vertInST[e.w]));
    }*/
    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t=G->adj[w];t!=G->z;t=t->next) {
            if(G->verticiCancellati[t->v]==0 && t->cancellato==0) {
                //printf("\tanalizzo %s - %s\n",STretrieveNome(G->tab,G->vertInST[w]),STretrieveNome(G->tab,G->vertInST[t->v]));
                if (pre[t->v] == -1) {
                    dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, archiB, count, isac);
                } else {
                    if (pre[t->v] > pre[w]) {
                       // printf("Arco B %s - %s\n",STretrieveNome(G->tab,G->vertInST[w]),STretrieveNome(G->tab,G->vertInST[t->v]));
                        *isac = 1;
                        trovato=0;
                        for(v=0;v<G->V;v++){
                            if(archiB[v].v==w && archiB[v].w==t->v){
                                trovato=1;
                            }
                        }
                            if (trovato ==0) {
                                archiB[*count] = EDGEcreate(w, t->v, t->wt);
                                (*count)++;

                        }
                    }
                }
            }

    }
    post[w]=(*time)++;
}
int *distinguiVertici(Edge *archi,int n){
    int *vert=malloc(n*sizeof(int));
    int i,j,k=0,trovatov=0,trovatow=0;
    for(i=0;i<n;i++){
        trovatov=0;
        trovatow=0;
        for(j=0;j<=k &&(trovatov==0||trovatow==0);j++){
            if(archi[i].v==vert[j]){
                trovatov=1;
            }
            if(archi[i].w==vert[j]){
                trovatow=1;
            }
        }
        if(trovatov==0){
            vert[k++]=archi[i].v;
        }
        if(trovatow==0){
            vert[k++]=archi[i].w;
        }
    }
    return vert;

}
int *GRAPHdfs(Graph G,int *n,int tipo){
    int v,num=0,time=0,*pre,*post,*st,isac=0;

    st=malloc(G->V*sizeof(int));
    pre=malloc(G->V*sizeof(int));
    post=malloc(G->V*sizeof(int));
    Edge *archiB=malloc(G->V*sizeof(Edge));
    for(v=0;v<G->V;v++){
        archiB[v]=EDGEcreate(-1,-1,-1);
    }
    for(v=0;v<G->V;v++){
        pre[v]=-1;
        post[v]=-1;
        st[v]=-1;
    }
    for(v=0;v<G->V;v++) {
        if (G->verticiCancellati[v] == 0) {
            if (pre[v] == -1)
                dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, archiB, &num, &isac);
        }
    }
    *n=num;
    free(st);
    free(pre);
    free(post);
    if(tipo==1) {
        return distinguiVertici(archiB, num);
    }
    return NULL;
}


void cancellaVertici(Graph G,int *sol,int k){
    int i,j;
    link t;
    //cancello archi che partono dal vertice da cancellare
    for(i=0;i<k;i++){
            for(t=G->adj[sol[i]];t!=G->z;t=t->next){
                t->cancellato=1;
                G->E1--;
               // printf("Cancello arco da %s a %s\n",STretrieveNome(G->tab,G->vertInST[sol[i]]),STretrieveNome(G->tab,G->vertInST[t->v]));
            }
            G->verticiCancellati[sol[i]]=1;

    }
    //cancello archi che arrivano nel vertice da considerare

    for (j = 0; j < G->V; j++) {
        if(G->verticiCancellati[j]==0) {
            for (t = G->adj[j]; t != G->z; t = t->next) {
                if (G->verticiCancellati[t->v] == 1) {
                    t->cancellato = 1;
                    G->E1--;
                  //  printf("Cancello arco da %s a %s\n",STretrieveNome(G->tab,G->vertInST[j]),STretrieveNome(G->tab,G->vertInST[t->v]));
                }
            }
        }
    }
    //G->V-=k;
}
void GraphResume(Graph G,int *sol,int k){
    int i,j;
    link t;
    for (j = 0; j < G->V; j++) {
        if(G->verticiCancellati[j]==0) {
            for (t = G->adj[j]; t != G->z; t = t->next) {
                if (G->verticiCancellati[t->v] == 1) {
                    t->cancellato = 0;
                    G->E1++;
                    // printf("Ripristino arco da %s a %s\n",STretrieveNome(G->tab,G->vertInST[j]),STretrieveNome(G->tab,G->vertInST[t->v]));
                }
            }
        }
    }
    for(i=0;i<k;i++){
        for(t=G->adj[sol[i]];t!=G->z;t=t->next){
            t->cancellato=0;
            G->E1++;
          //  printf("Ripristino arco da %s a %s\n",STretrieveNome(G->tab,G->vertInST[sol[i]]),STretrieveNome(G->tab,G->vertInST[t->v]));
        }
        G->verticiCancellati[sol[i]]=0;

    }

}

int isAciclico(Graph G){
    int nArchiB=0;
    GRAPHdfs(G,&nArchiB,0);
    if(nArchiB==0){
        return 1;
    }
    else{
        return 0;
    }
}
void dfsRcc(Graph G,int v,int id,int *cc){
    link t;
    cc[v]=id;
    for(t=G->adj[v];t!=G->z;t=t->next){
        if(G->verticiCancellati[t->v]==0 && t->cancellato==0) {
                if (cc[t->v] == -1 && G->verticiCancellati[t->v]==0) {
                    dfsRcc(G, t->v, id, cc);
                }
        }
    }
}
int *GRAPHcc(Graph G,int *ncc){
    int v,id=0,*cc;
    cc=malloc(G->V*sizeof(int));
    for(v=0;v<G->V;v++){
        cc[v]=-1;
    }
    for(v=0;v<G->V;v++){
        if(G->verticiCancellati[v]==0){
        if(cc[v]==-1)
            dfsRcc(G,v,id++,cc);
        }
    }
    *ncc=id;
    for(v=0;v<G->V;v++){
        if(cc[v]!=-1);
            //printf("Vertice : %s, C.C. :%d\n",STretrieveNome(G->tab,G->vertInST[v]),cc[v]);
    }
    return cc;
}


void GRAPHresumeArchi(Graph G,int *sol,int n){
    int i,j;
    link t;
    i=0;
    for(j=1;j<n;j++){
        GRAPHremove(G,EDGEcreate(sol[i],sol[j],-1));
    }

}
void mstV(Graph G,int *st,int *wt){
    int i,v,w,min,*fr=malloc(G->V*sizeof(int));
    for(v=0;v<G->V;v++){
        st[v]=-1;
        fr[v]=v;
        wt[v]=maxWT;
    }
    i=0;
    while(G->verticiCancellati[i]==1){
        i++;
    }
    st[i]=i;
    wt[i]=0;
    wt[G->V]=maxWT;
    for(min=i;min!=G->V;){
        if(G->verticiCancellati[min]==0) {
            v = min;
            st[min] = fr[min];
            for (w = 0, min = G->V; w < G->V; w++) {
                if (G->verticiCancellati[w] == 0) {
                    if (st[w] == -1) {
                        if ((G->MatrAdj[v][w]>0) && (G->MatrAdj[v][w] < wt[w])) {
                            wt[w] = G->MatrAdj[v][w];
                            fr[w] = v;
                        }
                        if (wt[w] < wt[min]) {
                            min = w;
                        }
                    }
                }
            }
        }
    }
}
int GRAPHmstP(Graph G){
    G=GRAPHmatr(G);
    int v,*st,*wt,weight=0;
    st=malloc(G->V*sizeof(int));
    wt=malloc((G->V+1)*sizeof(int));

    mstV(G,st,wt);
    for(v=0;v<G->V;v++) {
        if (G->verticiCancellati[v] == 0) {
            if (st[v] != v) {
                weight = weight + wt[v];
            }
        }
    }
    return weight;
}
void GraphPrint(Graph G){
    int i;
    link t;
    for(i=0;i<G->V;i++){
        if(G->verticiCancellati[i]==0) {
            for (t = G->adj[i]; t != G->z; t = t->next) {
                if (t->cancellato == 0) {
                    printf("Arco %s -- %s\n", STretrieveNome(G->tab, G->vertInST[i]),
                           STretrieveNome(G->tab, G->vertInST[t->v]));
                }
            }
        }
    }
}

