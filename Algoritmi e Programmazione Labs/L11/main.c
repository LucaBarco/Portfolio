#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAX 30
typedef struct CC{
    int *vertici;
    int n;
    int cont;
}CompConn;
void trovaVertici(Graph G,int *vertici,int n,int **distMin);
void comb_sempl(int pos,int start,int *sol,int *vertici,int n,int k,int *finito,Graph G,int **distMin,int *cont);
void trovaArchi(Graph G,int ncc,int *cc,int **distMin);
void princ_molt(int pos,CompConn *val,int *sol,int n,Graph G,int *minwtMST,int *bestsol,int *bestsol1,int **distMin);
void stampaVertici(int *sol,int n,Graph G);
void printNewArchi(int *bestsol,int ncc,int peso,Graph G);
int provaArchi(Graph G,int *val,int n,int **matr,int *bestsol1);
void dispsempl(int pos,int *val,int *sol,int *mark,int n,Graph G,int **matr,int *peso,int *minpeso,int *bests);
int pesoMin(int *val,int n,Graph G,int **matr);
int main(int argc,char **argv) {
    Graph G;
    FILE *fp;
    int **distMin;
    int i=0,j,N;
    int *vertici;
    fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return -1;
    }
    fscanf(fp,"%d",&N);
    G=GRAPHinit(N);
    GraphSTread(fp,G);
    G=GRAPHread(fp,G);
    fclose(fp);

    distMin=GRAPHminDist(G);
    /*for(i=0;i<GraphCount(G);i++){
        for(j=0;j<GraphCount(G);j++){
            printf("%d ",distMin[i][j]);
        }
        printf("\n");
    }*/
    vertici=malloc(GraphCount(G)*sizeof(int));

    for(i=0;i<GraphCount(G);i++){
        vertici[i]=i;
       // printf("-%s\n",GRAPHstRetrieve(G,vertici[i]));
    }
    trovaVertici(G,vertici,GraphCount(G),distMin);
    return 0;
}
/*
    -> funzione di powerset sui vertici

    -> provo a cancellarli

    -> se ottengo un grafo aciclico, "blocco" il powerset su quella cardinalità

    -> se,cancellando i vertici e trovando un grafo aciclico,trovo un grafo sconnesso ,lo connetto con un'opportuna selezione combinatoria di archi
        (calcolo componenti connesse,divido i vertici per componenti connesse e applico il principio di moltiplicazione,
        e una volta ottenuto un sottoinsieme di vertici da poter connettere,applico le permutazioni semplici per
        trovare la combinazione migliore di archi)

    -> se non riottengo un ciclo calcolo MST,altrimenti scarto la soluzione, e se è minore del MST minimo attuale,aggiorno la soluzione

    -> procedo calcolando tutti i sottoinsiemi di vertici con quella cardinalità
    */

void trovaVertici(Graph G,int *vertici,int n,int **distMin){
    int i,j,finito=0,num=0;
    int *sol=malloc(n*sizeof(int));
    for(j=0;j<n;j++){
        sol[j]=-1;
    }
    for(i=1;i<=n && finito==0;i++){
        comb_sempl(0,0,sol,vertici,n,i,&finito,G,distMin,&num);
    }
    printf("Insiemi trovati: %d\n",num);
}

void comb_sempl(int pos,int start,int *sol,int *vertici,int n,int k,int *finito,Graph G,int **distMin,int *cont){
    int i,ncc;
    int *cc;
    if(pos>=k){
        cancellaVertici(G,sol,k);

        if(isAciclico(G)==1){
            (*cont)++;
            if(*finito==0){
                    printf("Insiemi di cardinalita' %d\n",k);
            }
            *finito=1;
            cc=GRAPHcc(G,&ncc);
            stampaVertici(sol,k,G);

            if(ncc>1){

                trovaArchi(G,ncc,cc,distMin);
            }
            else {
                printf("Grafo Connesso!\n\n");
            }
        }
        GraphResume(G,sol,k);
        return;
    }
    for(i=start;i<n;i++){
        sol[pos]=vertici[i];
        comb_sempl(pos+1,i+1,sol,vertici,n,k,finito,G,distMin,cont);
    }
}
void trovaArchi(Graph G,int ncc,int *cc,int **distMin){
    CompConn *elenco=malloc(ncc*sizeof(CompConn));
    int *contatori=calloc(ncc,sizeof(int));
    int *sol=malloc(ncc*sizeof(int));
    int *bestsol=malloc(ncc*sizeof(int));
    int *bestsol1=malloc(ncc*sizeof(int));
    int i,j,pesoMST=1000;
    for(i=0;i<ncc;i++){
        sol[i]=-1;
        bestsol[i]=-1;
        bestsol1[i]=-1;
    }
    for(i=0;i<GraphCount(G);i++){
        if(cc[i]!=-1) {
            contatori[cc[i]]++;
        }
    }
    for(i=0;i<ncc;i++){
        elenco[i].n=contatori[i];
        elenco[i].vertici=malloc(contatori[i]*sizeof(int));
        for(j=0;j<contatori[i];j++){
            elenco[i].vertici[j]=-1;
        }
        elenco[i].cont=0;
    }
    for(i=0;i<GraphCount(G);i++){
        if(cc[i]!=-1) {
            elenco[cc[i]].vertici[elenco[cc[i]].cont] = i;

            elenco[cc[i]].cont++;
        }
    }
    princ_molt(0,elenco,sol,ncc,G,&pesoMST,bestsol,bestsol1,distMin);
    printNewArchi(bestsol,ncc,pesoMST,G);
}
void princ_molt(int pos,CompConn *val,int *sol,int n,Graph G,int *minwtMST,int *bestsol,int *bestsol1,int **distMin){
    int i,peso;
    if(pos>=n){
        peso=provaArchi(G,sol,n,distMin,bestsol1);
        if(peso<*minwtMST){
            *minwtMST=peso;
            for(i=0;i<n;i++){
                bestsol[i]=bestsol1[i];
            }
        }
        return;
    }
    for(i=0;i<val[pos].n;i++){
        sol[pos]=val[pos].vertici[i];
        princ_molt(pos+1,val,sol,n,G,minwtMST,bestsol,bestsol1,distMin);
    }
}
void stampaVertici(int *sol,int n,Graph G){
    int i;
    printf("Nodi eliminati :\n\t");
    for(i=0;i<n;i++){
        printf("---> %s\n\t",GRAPHstRetrieve(G,sol[i]));
    }
}
void printNewArchi(int *bestsol,int ncc,int peso,Graph G){
    int i,j=0;
    printf("Grafo non connesso! \n\n\tAggiunta dei seguenti Archi:\n");
    for(i=1;i<ncc;i=i+2) {
        if (bestsol[i] != -1) {
            printf("\t- Arco  %s - %s\n", GRAPHstRetrieve(G, bestsol[j]), GRAPHstRetrieve(G, bestsol[i]));
        }
    }
    printf("\n");
}
int provaArchi(Graph G,int *val,int n,int **matr,int *bestsol1){
    int peso=0,minpeso=1000;
    int *sol1=malloc(n*sizeof(int));
    int *mark=calloc(n,sizeof(int));
    dispsempl(0,val,sol1,mark,n,G,matr,&peso,&minpeso,bestsol1);
    return minpeso;

}
void dispsempl(int pos,int *val,int *sol,int *mark,int n,Graph G,int **matr,int *peso,int *minpeso,int *bests){
    int i;
    if(pos>=n){
        *peso=pesoMin(sol,n,G,matr);
        if(*peso<*minpeso){
            *minpeso=*peso;
            for(i=0;i<n;i++){
                bests[i]=sol[i];
            }
        }
        return ;
    }
    for(i=0;i<n;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=val[i];
            dispsempl(pos+1,val,sol,mark,n,G,matr,peso,minpeso,bests);
            mark[i]=0;
        }
    }
}
int pesoMin(int *val,int n,Graph G,int **matr){
    int i,j,peso;
    j=0;
    for(i=1;i<n;i++) {
            GRAPHinsert(G, EDGEcreate(val[j], val[i], matr[val[j]][val[i]]));
    }
    peso=GRAPHmstP(G);
    GRAPHresumeArchi(G,val,n);
    return peso;
}