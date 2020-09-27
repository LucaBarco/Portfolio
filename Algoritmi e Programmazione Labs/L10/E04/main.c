#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct coord{
    int r;
    int c;
}Coordinate;
typedef struct livello{

    int n,s,e,w;
}*Livello;
char **leggiFile(char *nome,int *nr,int *nc);
void trovacammino(char **labirinto,int nr,int nc);
void esploraR(int pos,char **labirinto,int nr,int nc,Livello elenco,Coordinate *cammino,Coordinate *bestcammino,int *bestlungh,int lungh,int **visitato);

int main() {
    int nr,nc,i,j;
    char nome[]={"lab.txt"};
    char **labirinto=leggiFile(nome,&nr,&nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nr;j++){
            printf("%c ",labirinto[i][j]);
        }
        printf("\n");
    }
    trovacammino(labirinto,nr,nc);
    return 0;
}
char **leggiFile(char *nome,int *nr,int *nc){
    FILE *fp=fopen(nome,"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    int r,c,i,j;
    char temp;
    fscanf(fp,"%d %d\n",&r,&c);
    *nr=r;
    *nc=c;
    char **labirinto=malloc(r*sizeof(char*));
    for(i=0;i<r;i++){
        labirinto[i]=malloc(c*sizeof(char));
    }
    i=0;j=0;
    while(fscanf(fp,"%c",&temp)!=EOF){
        if(!isspace(temp)) {
            labirinto[i][j]=temp;
            if (j == c - 1) {
                i++;
                j = 0;
            } else {
                j++;
            }
        }
    }
    fclose(fp);
    return labirinto;
}
/* Basandomi sul principio di moltiplicazione, per ogni casella verifico se è possibile spostarsi a nord,sud,est ovest
 * Memorizzo il cammino come un vettore di coordinate
 * faccio partire la ricorsione dal punto di partenza I
 * Per ottenere un cammino semplice uso una matrice di interi ausiliaria "visitato"
 *
 * */

void trovacammino(char **labirinto,int nr,int nc){
    Livello elenco=malloc(nr*nc*sizeof(*elenco));
    int i,j,finito=0,bestlungh=10000,res;
    int **visitato=malloc(nr*sizeof(int *));
    Coordinate p,*cammino=malloc(nr*nc*sizeof(*cammino)),*best=malloc(nr*nc*sizeof(*best));

    for(i=0;i<nr;i++){
        visitato[i]=calloc(nc,sizeof(int));
    }
    for(i=0;i<nr*nc;i++){
        elenco[i].n=elenco[i].w=elenco[i].e=elenco[i].s=0;
    }
    //verifico le direzioni
    for(i=0;i<nr;i++){
       for(j=0;j<nc;j++){
           if(labirinto[i][j]!='X'){
              if(i>0 && labirinto[i-1][j]!='X') {
                  elenco[(i * nc) + j].n=1;
              }
               if(i<nr-1 && labirinto[i+1][j]!='X') {
                   elenco[(i * nc) + j].s=1;
               }
               if(j>0 && labirinto[i][j-1]!='X') {
                   elenco[(i * nc) + j].w=1;
               }
               if(j<nc-1 && labirinto[i][j+1]!='X') {
                   elenco[(i * nc) + j].e=1;
               }
           }
       }
    }
   /* for(i=0;i<nr*nc;i++){
        printf("n=%d s=%d e=%d w=%d\n",elenco[i].n,elenco[i].s,elenco[i].e,elenco[i].w);
    }*/

    for(i=0;i<nr*nc;i++){
        cammino[i].r=cammino[i].c=-1;
        best[i].r=best[i].c=-1;
    }
    //cerco punto di partenza
    p.r=0;
    p.c=0;
    for(i=0;i<nr && finito==0;i++){
        for(j=0;j<nc && finito==0;j++) {
            if(labirinto[i][j]=='I'){
                p.r=i;
                p.c=j;
                finito=1;
            }
        }
    }
    cammino[0]=p;
    visitato[p.r][p.c]=1;
    esploraR(0,labirinto,nr,nc,elenco,cammino,best,&bestlungh,0,visitato);
    res=0;
    for(i=0;i<nr*nc;i++){
        if(best[i].c != -1 && best[i].r!=-1){
           res=1;
        }
    }
    if(res==0){
        printf("Nessun cammino trovato!\n");
    }
    else{
        printf("Cammino trovato:\n");
        for(i=0;i<nr*nc;i++){
            if(best[i].c != -1 && best[i].r!=-1){
                printf("<%d,%d>\n",best[i].r,best[i].c);
            }
        }
        printf("Lunghezza del cammino: %d\n",bestlungh);
    }
}
void esploraR(int pos,char **labirinto,int nr,int nc,Livello elenco,Coordinate *cammino,Coordinate *bestcammino,int *bestlungh,int lungh,int **visitato){
    int i;
    //printf("%c \n",labirinto[cammino[pos].r][cammino[pos].c]);
    if(labirinto[cammino[pos].r][cammino[pos].c]=='U'){
        if(lungh<*bestlungh){
            *bestlungh=lungh;
            for(i=0;i<nr*nc;i++){
                bestcammino[i]=cammino[i];
            }
        }
        return ;
    }
    if(pos>=nr*nc){
        return ;
    }
    /*
     * Il ciclo for è "esploso" nei 4 casi in cui sia possibile andare a nord,sud,est,ovest
     */
    //printf("n=%d s=%d e=%d w=%d\n",elenco[nc*cammino[pos].r+cammino[pos].c].n,elenco[nc*cammino[pos].r+cammino[pos].c].s,elenco[nc*cammino[pos].r+cammino[pos].c].e,elenco[nc*cammino[pos].r+cammino[pos].c].w);
        if(elenco[nc*cammino[pos].r+cammino[pos].c].n==1){
            cammino[pos+1].r=cammino[pos].r-1;
            cammino[pos+1].c=cammino[pos].c;
           // printf("%d,%d\n",cammino[pos+1].r,cammino[pos+1].c);
            if(visitato[cammino[pos+1].r][cammino[pos+1].c]==0) {
                visitato[cammino[pos+1].r][cammino[pos+1].c]=1;
                 esploraR(pos + 1, labirinto, nr, nc, elenco, cammino, bestcammino, bestlungh, lungh + 1,visitato);
                visitato[cammino[pos+1].r][cammino[pos+1].c]=0;
                lungh -= 1;
            }
                cammino[pos+1].r = -1;
                cammino[pos+1].c = -1;

        }
        if(elenco[nc*cammino[pos].r+cammino[pos].c].s==1){
            cammino[pos+1].r=cammino[pos].r+1;
            cammino[pos+1].c=cammino[pos].c;
            //printf("%d,%d\n",cammino[pos+1].r,cammino[pos+1].c);
            if(visitato[cammino[pos+1].r][cammino[pos+1].c]==0) {
                visitato[cammino[pos+1].r][cammino[pos+1].c] = 1;
                 esploraR(pos + 1, labirinto, nr, nc, elenco, cammino, bestcammino, bestlungh, lungh + 1,
                               visitato);
                visitato[cammino[pos+1].r][cammino[pos+1].c]=0;
                lungh -= 1;
            }
            cammino[pos+1].r=-1;
            cammino[pos+1].c=-1;
        }
        if(elenco[nc*cammino[pos].r+cammino[pos].c].e==1){
            cammino[pos+1].r=cammino[pos].r;
            cammino[pos+1].c=cammino[pos].c+1;
           // printf("%d,%d\n",cammino[pos+1].r,cammino[pos+1].c);
            if(visitato[cammino[pos+1].r][cammino[pos+1].c]==0) {
                visitato[cammino[pos+1].r][cammino[pos+1].c] = 1;
                 esploraR(pos + 1, labirinto, nr, nc, elenco, cammino, bestcammino, bestlungh, lungh + 1,
                               visitato);
                visitato[cammino[pos+1].r][cammino[pos+1].c]=0;
                lungh -= 1;
            }
            cammino[pos+1].r=-1;
            cammino[pos+1].c=-1;
        }
        if(elenco[nc*cammino[pos].r+cammino[pos].c].w==1){
            cammino[pos+1].r=cammino[pos].r;
            cammino[pos+1].c=cammino[pos].c-1;
            //printf("%d,%d\n",cammino[pos+1].r,cammino[pos+1].c);
            if(visitato[cammino[pos+1].r][cammino[pos+1].c]==0) {
                visitato[cammino[pos+1].r][cammino[pos+1].c] = 1;
                 esploraR(pos + 1, labirinto, nr, nc, elenco, cammino, bestcammino, bestlungh, lungh + 1,
                               visitato);
                visitato[cammino[pos+1].r][cammino[pos+1].c]=0;
                lungh -= 1;
            }
            cammino[pos+1].r=-1;
            cammino[pos+1].c=-1;
        }
    return;
}