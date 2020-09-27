#include <stdio.h>
#include <stdlib.h>
typedef struct famiglia_s famiglia;
typedef struct koala_s{
    int id;
    int *alberi;
    int n_alb;
    famiglia *fam;
}koala;


struct famiglia_s{
    int id;
    koala **membri;
};

koala *leggiFile_hab(koala *v,int *n,int *alberi);
famiglia *leggiFile_fam(famiglia *v,int *n,koala *k);
int **leggiFile_nem(int **matr,int n);
void generaalberi(koala *v,famiglia *f,int n_alberi,int n_koala,int maxkoala,int tiposol,int **matr);
void dispRip_R(int pos,int *val,int *sol,int n_alberi,int n_koala,int maxkoala,int start, koala *v, famiglia *f,int *finito,int **matr,int tiposol);
int controllaSol(int *sol,int n_alberi,int n_koala,int maxkoala,koala *v,famiglia *f,int **matr,int tiposol);
void stampaSol(int *sol, int n_koala);
int controllaOcc(int *sol,int n_alberi,int n_koala,int max,int j);
int nemiche(int *sol,int n_koala,int **matr,koala *v,int pos);

int main(int argc, char **argv) {
    koala *elenco_koala;
    famiglia *elenco_famiglie = NULL;
    int m,n_koala,n_alberi,n_famiglie,i;
    int **nemici;

    if(argc<2){
        printf("Errore nell'inserimento dei parametri!\n");
        return -1;
    }
    m=atoi(argv[1]);

    elenco_koala=leggiFile_hab(elenco_koala,&n_koala,&n_alberi);

    elenco_famiglie=leggiFile_fam(elenco_famiglie,&n_famiglie,elenco_koala);

    nemici=malloc(n_famiglie*sizeof(int*));

    for(i=0;i<n_famiglie;i++){
        nemici[i]=calloc(n_famiglie,sizeof(int));
    }

    nemici=leggiFile_nem(nemici,n_famiglie);
    printf("Soluzione 1:\n");
    generaalberi(elenco_koala,elenco_famiglie,n_alberi,n_koala,m,1,nemici);
    printf("Soluzione 2:\n");
    generaalberi(elenco_koala,elenco_famiglie,n_alberi,n_koala,m,2,nemici);

    free(elenco_famiglie);
    free(elenco_koala);
    for(i=0;i<n_famiglie;i++){
        free(nemici[i]);
    }
    free(nemici);

    return 0;
}
koala *leggiFile_hab(koala *v,int *n,int *alberi){
    FILE *fp;
    int i=0,j,n_alb=0;
    fp=fopen("hab.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d",n);
    v=malloc(*n*sizeof(koala));
    while(i<*n){
        v[i].id=i;
        fscanf(fp,"%d",&v[i].n_alb);
        v[i].alberi=malloc(v[i].n_alb*sizeof(int));
        for(j=0;j<v[i].n_alb;j++){
            fscanf(fp,"%d",&v[i].alberi[j]);
            if(n_alb<v[i].alberi[j]){
                n_alb=v[i].alberi[j];
            }
        }
        i++;
    }
    *alberi=n_alb+1;
    fclose(fp);
    return v;
}
famiglia *leggiFile_fam(famiglia *v,int *n,koala *k){
    FILE *fp;
    int i,j,N,membro_temp;

    fp=fopen("fam.txt","r");

    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }

    fscanf(fp,"%d",n);

    v=malloc((*n)*sizeof(famiglia));

    for(i=0;i<*n;i++){

        v[i].id=i;

        fscanf(fp,"%d",&N);

        v[i].membri=malloc(sizeof(koala*));

        for(j=0;j<N;j++){

            fscanf(fp,"%d",&membro_temp);

            v[i].membri[j]=&k[membro_temp];

            k[membro_temp].fam=&v[i];

        }
    }
    fclose(fp);
    return v;
}
int **leggiFile_nem(int **matr,int n){
    FILE *fp;
    int id1,id2,i=0;
    fp=fopen("nem.txt","r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    while(fscanf(fp,"%d %d",&id1,&id2)!=EOF){
        matr[id1][id2]=1;
        matr[id2][id1]=1;
    }
    fclose(fp);
    return matr;
}
void generaalberi(koala *v,famiglia *f,int n_alberi,int n_koala,int maxkoala,int tiposol,int **matr){
    int i,finito=0,nosol=0;
    int * val=malloc(n_alberi*sizeof(int));
    for(i=0;i<n_alberi;i++){
        val[i]=i;
    }
    int *sol=calloc(n_koala,sizeof(int));
    dispRip_R(0,val,sol,n_alberi,n_koala,maxkoala,0,v,f,&finito,matr,tiposol);
    if(finito==0){
        printf("Nessuna soluzione trovata!\n");
    }
    return;
}
void dispRip_R(int pos,int *val,int *sol,int n_alberi,int n_koala,int maxkoala,int start, koala *v, famiglia *f,int *finito,int **matr,int tiposol){
    int i;
    if(pos>=n_koala){

        if(controllaSol(sol,n_alberi,n_koala,maxkoala,v,f,matr,tiposol)==1) {
            printf("Sol:\n");
            stampaSol(sol, n_koala);
            *finito = 1;
        }
        return;
    }

    for(i=start;i<n_alberi && *finito==0 ;i++){
        sol[pos] = val[i];
        if(controllaOcc(sol,n_alberi,n_koala,maxkoala,pos)==1 && nemiche(sol,n_koala,matr,v,pos)==1) {
            dispRip_R(pos + 1, val, sol, n_alberi, n_koala, maxkoala, start, v, f, finito, matr, tiposol);
        }
    }
    return ;
}
int controllaSol(int *sol,int n_alberi,int n_koala,int maxkoala,koala *v,famiglia *f,int **matr,int tiposol){
    int i,j;
    int trov=0;

    if(tiposol==2){
        //controllo su vivibilità dei koala
        for(i=0;i<n_koala;i++){
            trov=0;
            for(j=0;j<v[i].n_alb;j++){
                if(sol[i]==v[i].alberi[j]){
                    trov=1;
                }
            }
            if(trov==0){
                return 0;
            }
        }
        return 1;
    }

    return 1;
}
void stampaSol(int *sol, int n_koala){
    int i,max;

    for(i=0;i<n_koala;i++) {
        printf("koala %d -> Albero: %d\n",i,sol[i]);
    }

    return ;
}
int controllaOcc(int *sol,int n_alberi,int n_koala,int max,int j){
    int *occ=calloc(n_alberi,sizeof(int));
    int i;
//controllo su max numero di koala per albero
    for(i=0;i<=j;i++){
        occ[sol[i]]++;
    }
    for(i=0;i<n_alberi;i++){
    if(occ[i]>max){
        return 0;
        }
    }
return 1;
}
int nemiche(int *sol,int n_koala,int **matr,koala *v,int pos){
 int i,j;
    for(i=0;i<pos;i++) {
        for (j = i + 1; j <=pos; j++) {
            if (sol[i] == sol[j]) {
                if (matr[v[i].fam->id][v[j].fam->id]==1){
                    return 0;
                }
            }
        }
    }
    return 1;
}