#include <stdio.h>
#include <stdlib.h>
typedef struct structMatr_s{
    int scambi;
    int estremo_sx;
    int estremo_dx;
    int dimensione;
    int *freccescambiate;
}structMatr;

int *leggiFile(char *nome,int *N);
//SOL.Combinatoria
int minimiScambi_comb(int *frecce,int N);
void permutazioni(int pos,int *sol,int *bestsol,int *val,int *frecce,int *mark,int N,int k,int scambi,int *bestscambi);
int controllaSol(int *sol,int N);
//SOL.Programmazione Dinamica
int cercaMinSOl(int *frecce,int nfrecce);
int nscambi(int *frecce,structMatr **matr,int i,int j);
int *creasol(structMatr **matr,int *scambi,int *frecce,int N,int *sol);
void stampaSol(int *sol,int N,int scambi);

int main(int argc, char **argv) {

    int *frecce,nfrecce,nscambi,i;
    if(argc<2){
        printf("Errore nell'inserimento dei parametri!\n");
    }

    frecce=leggiFile(argv[1],&nfrecce);
    if(frecce!=NULL) {
        printf("Situazione: \n\t");
        for(i=0;i<nfrecce;i++){
            if(frecce[i]==0)
                printf("-> ");
            if(frecce[i]==1){
                printf("<- ");
            }
        }
        printf("\n\n");
        //SOL. Combinatoria
        nscambi = minimiScambi_comb(frecce, nfrecce);
        printf("---->Numero minimo di scambi: %d\n\n",nscambi);

        //SOL. Programmazione Dinamica
        nscambi=cercaMinSOl(frecce,nfrecce);
        printf("\n---->Numero minimo di scambi: %d\n",nscambi);
    }
    else{
        printf("Errore nell'apertura del file!\n");
    }
    return 0;
}
int *leggiFile(char *nome,int *N){
    FILE *fp;
    int *frecce,i=0;
    fp=fopen(nome,"r");
    if(fp==NULL){
        return NULL;
    }
    fscanf(fp,"%d",N);
    frecce=malloc(*N*sizeof(int));
    while(fscanf(fp,"%d",&frecce[i])!=EOF && i<*N){
        i++;
    }
    return frecce;
}


//SOL. Combinatoria

int minimiScambi_comb(int *frecce,int N){
    int *sol=malloc(N*sizeof(int));
    int *bestsol=malloc(N*sizeof(int));
    int *val=malloc(2*sizeof(int));
    int *mark=calloc(2,sizeof(int));
    int i,min=N,k=2;
    val[0]=0;
    val[1]=1;
    mark[0]=mark[1]=N/2;

    permutazioni(0,sol,bestsol,val,frecce,mark,N,k,0,&min);
    printf("Soluzione combinatoria: \n\t");
    for(i=0;i<N;i++){
        if(bestsol[i]==0)
            printf("-> ");
        if(bestsol[i]==1){
            printf("<- ");
        }
    }
    printf("\n");
    return min;
}
void permutazioni(int pos,int *sol,int *bestsol,int *val,int *frecce,int *mark,int N,int k,int scambi,int *bestscambi){
    int i;
    if(pos>=N){
        //printf("scambi: %d ",scambi);
        if(controllaSol(sol,N)==1) {
            if (scambi < *bestscambi) {
                *bestscambi=scambi;
                for (i = 0; i < N; i++) {
                    bestsol[i] = sol[i];
                }
            }
        }
        return ;
    }
    for(i=0;i<k;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=val[i];
            if(sol[pos]!=frecce[pos]){
                scambi++;
            }
            permutazioni(pos+1,sol,bestsol,val,frecce,mark,N,k,scambi,bestscambi);
            //smarcamento
            mark[i]++;
            if(sol[pos]!=frecce[pos]){
                scambi--;
            }

        }
    }
    return ;
}
int controllaSol(int *sol,int N) {
    int i = 0, nfr_sx = 0, nfr_dx = 0, stop = 0, dx = 0, comb;


    /* printf("Soluzione temp: \n\t");
     for(i=0;i<N;i++){
         if(sol[i]==0)
             printf("-> ");
         if(sol[i]==1){
             printf("<- ");
         }
     }
     printf("\n");*/

    if(sol[0]==1||sol[N-1]==0) {
        stop=1;
    }
    i=0;
    comb=sol[i];

    while(i<N && stop==0){

        if(sol[i]==comb){
            if (dx==1) nfr_dx++;
            if(dx==0) nfr_sx++;
        }
        else{
            comb=sol[i];
            if(dx==1){
                if(nfr_dx!=nfr_sx){
                    stop=1;
                }
                else{
                    dx=0;
                    nfr_sx=1;
                    nfr_dx=0;
                }
            }
            else {
                dx = 1;
                nfr_dx = 1;
            }
        }
        i++;
    }
    if(stop==1) {
        return 0;
    }
    return 1;
}

//SOL. Programmazione Dinamica

int cercaMinSOl(int *frecce,int N){

    int i,j,a,b,p=0,minsc=0,dim;

    int *sol=calloc(N,sizeof(int));
    for(i=0;i<N;i++){
        sol[i]=frecce[i];
    }
    //costruzione tabella
    structMatr **matr=malloc((N/2)*sizeof(structMatr *));
    for(i=0;i<N/2;i++){
        matr[i]=malloc((N/2)*sizeof(structMatr));
    }
    for(i=0;i<N/2;i++){
        for(j=0;j<N/2;j++){
            matr[i][j].scambi=N+10; //assegnazione valore arbitrario
            matr[i][j].freccescambiate=calloc(N,sizeof(int));
        }
    }
    //Compilazione tabella dei costi
    for(j=0;j<N/2;j++){
        for(i=0;i<N/2;i++){
            dim=2*(j+1);
            a=2*i;
            b=a+dim-1;
            if(a<N&&b<N) {
                matr[j][i].dimensione = dim;
                matr[j][i].estremo_sx =a;
                matr[j][i].estremo_dx = b;
                matr[j][i].scambi = nscambi(frecce, matr, j, i);
            }
            else{
                matr[i][j].scambi=N+10;
            }
        }
    }
    printf("Soluzione Programmazione Dinamica:\n\t");
    for(i=0;i<N/2;i++) {
        for (j = 0; j < N / 2; j++) {
            for(p=0;p<N;p++) {
                if(matr[i][j].freccescambiate[p]==1) {
                }
            }
        }
    }
    sol=creasol(matr,&minsc,frecce,N,sol);
    stampaSol(sol,N,minsc);
    return minsc;
}

int nscambi(int *frecce,structMatr **matr,int i,int j){
    int l,met;
    int scambi=0;

    for(l=matr[i][j].estremo_sx;l<=matr[i][j].estremo_dx;l++){
        met=(matr[i][j].estremo_sx+matr[i][j].estremo_dx)/2;
        if(l<=met){
            if(frecce[l]!=0){
                scambi++;
                matr[i][j].freccescambiate[l]=1;
            }
        }
        else{
            if(frecce[l]!=1){
                scambi++;
                matr[i][j].freccescambiate[l]=1;
            }
        }
    }

    return scambi;

}
int *creasol(structMatr **matr,int *scambi,int *frecce,int N,int *sol){
    int i,j,mincurr=N+1,a=0,finito=0,fincol=0,p;
    int indici[2]={0,0};
    *scambi=0;
    for(i=0;i<N/2;i++) {
        fincol = 0;
        j = 0;
        if (matr[j][i].estremo_sx == a) {
            mincurr = matr[j][i].scambi;
            indici[0] = j;
            indici[1] = i;
        } else {
            fincol = 1;
        }
        if (fincol == 0) {
            finito = 0;
            for (j = 0; j < N / 2 && finito == 0 && fincol == 0; j++) {
                if (matr[j][i].scambi != N + 10) {
                    if (matr[j][i].scambi <= mincurr && matr[j][i].estremo_sx == a) {
                        mincurr = matr[j][i].scambi;
                        a = matr[j][i].estremo_sx;
                        indici[0] = j;
                        indici[1] = i;
                    }
                } else {
                    finito = 1;
                }
            }
            for (p = 0; p < N; p++) {
                if (matr[indici[0]][indici[1]].freccescambiate[p] == 1) {
                    if (sol[p] == 0) {
                        sol[p] = 1;
                    }
                    else {
                        if (sol[p] == 1) {
                            sol[p] = 0;
                        }
                    }
                }
            }
            *scambi = *scambi + mincurr;
            a = matr[indici[0]][indici[1]].estremo_dx + 1;
        }
    }
    return sol;
}
void stampaSol(int *sol,int N,int scambi){
    int i;
    for(i=0;i<N;i++){
        if(sol[i]==0){
            printf("-> ");
        }
        if(sol[i]==1){
            printf("<- ");
        }
    }
    return ;
}