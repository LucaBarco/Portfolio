#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct esercizio_s{
    char *nome;
    int grado;
    float punti;
    int nE;
    int rapp;
    int inSol;
}ES;
typedef struct piano_s{
    ES *id;
    int bonus;
    int rip;
}piano;

typedef struct atleta_s{
    int maxNA;
    int maxAA;
    int maxAI;
    int maxSUM;
}atleta;


void leggiFile(ES **elenco,FILE *fp,int NA,int AA,int AI);
atleta leggiAtleta();
ES *ordinamento(ES **elenco,int dim);
void MergeSort(int l,int r,ES** elenco,ES **temp);
void Merge(int l, int m, int r, ES **elenco, ES **temp);
ES **creaElenco(ES **elenco,atleta atl,int NA,int AA,int AI,int *el);
piano ** creaSolGreedy(ES **elenco,int esGara,int NA,int AA,int AI,int *bonus,atleta atl,float *point,int el);
void stampaSol(ES **elenco,piano **sol,int esGara,int *bonus,float punteggio);
int main() {

    int NA,AA,AI,i,el=0;
    int bonus[2]={0,0};
    int esGara=8;
    float punti=0;
    piano **sol;
    ES **elenco,**nuovoelenco;
    atleta atl;
    FILE *fp=fopen("elementi.txt","r");
    fscanf(fp,"%d %d %d\n",&NA,&AA,&AI);
    elenco=malloc((NA+AA+AI)*sizeof(*elenco));
    for(i=0;i<(NA+AA+AI);i++){
        elenco[i]=malloc(sizeof(ES));
    }
    leggiFile(elenco,fp,NA,AA,AI);
    fclose(fp);

    atl=leggiAtleta();
    nuovoelenco=creaElenco(elenco,atl,NA,AA,AI,&el);
    sol=creaSolGreedy(nuovoelenco,esGara,NA,AA,AI,bonus,atl,&punti,el);
    stampaSol(nuovoelenco,sol,esGara,bonus,punti);


    return 0;
}

void leggiFile(ES **elenco,FILE *fp,int NA,int AA,int AI){

    int i,finito=0;
    char nome[50];
    float punti;
    int grado;

    for(i=0;i<NA&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elenco[i]->punti=punti;
            elenco[i]->grado=grado;
            elenco[i]->nome = strdup(nome);
            elenco[i]->nE=1;
            elenco[i]->rapp=(int)(8/grado);
            elenco[i]->inSol=0;
        }
        else{
            finito=1;
        }
    }

    finito=0;
    for(i=NA;i<(NA+AA)&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elenco[i]->punti=punti;
            elenco[i]->grado=grado;
            elenco[i]->nome = strdup(nome);
            elenco[i]->nE=2;
            elenco[i]->rapp=(int)(8/grado);
            elenco[i]->inSol=0;
        }
        else{
            finito=1;
        }
    }
    finito=0;
    for(i=(NA+AA);i<(NA+AA+AI)&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elenco[i]->punti=punti;
            elenco[i]->grado=grado;
            elenco[i]->nome = strdup(nome);
            elenco[i]->nE=3;
            elenco[i]->rapp=(int)(8/grado);
            elenco[i]->inSol=0;
        }
        else{
            finito=1;
        }
    }

}

atleta leggiAtleta(){
    atleta x;
    printf("\nInserire i dati dell'atleta!\n");
    printf("MAX difficolta' per esercizi NON ACROBATICI: ");
    scanf("%d",&x.maxNA);
    printf("MAX difficolta' per esercizi ACROBATICI AVANTI: ");
    scanf("%d",&x.maxAA);
    printf("MAX difficola' per esercizi ACROBATICI INDIETRO: ");
    scanf("%d",&x.maxAI);
    printf("MAX difficola' TOTALE: ");
    scanf("%d",&x.maxSUM);
    return x;
}

ES *ordinamento(ES **elenco,int dim){
    int l=0,r=dim-1,i;
    ES **temp=malloc(dim*sizeof(*temp));
    for(i=0;i<dim;i++){
        temp[i]=malloc(sizeof(ES));
    }
    MergeSort(l,r,elenco,temp);


}
void MergeSort(int l,int r,ES** elenco,ES **temp){
    int m=(l+r)/2;
    if(r<=l)
        return;
    MergeSort(l,m,elenco,temp);
    MergeSort(m+1,r,elenco,temp);
    Merge(l,m,r,elenco,temp);
}

void Merge(int l, int m, int r, ES **elenco, ES **temp) {
    int i,j,k;
    i=l;
    j=m+1;
    for(k=l;k<=r;k++){
        if(i>m){
            temp[k]=elenco[j++];
        }
        else if(j>r){
            temp[k]=elenco[i++];
        }
        else if(elenco[i]->rapp>=elenco[j]->rapp){
            temp[k]=elenco[i++];
        }
        else {
            temp[k]=elenco[j++];
        }

    }
    for(k=l;k<=r;k++){
        elenco[k]=temp[k];
    }
    return;
}

ES **creaElenco(ES **elenco,atleta atl,int NA,int AA,int AI,int *n){
    int i,j=0,el=0;
    ES **nuovo=malloc((NA+AA+AI)*sizeof(*nuovo));
    for(i=0;i<(NA+AA+AI);i++){
        nuovo[i]=malloc(sizeof(ES));
    }
    ES **temp;
    for(i=0;i<(NA);i++) {
        if (elenco[i]->grado <= atl.maxNA) {
            nuovo[j++] = elenco[i];
        }
    }
    for(i=NA;i<(NA+AA);i++){
            if(elenco[i]->grado<=atl.maxAA){
                nuovo[j++]=elenco[i];
            }
    }
    for(i=(NA+AA);i<(NA+AA+AI);i++) {
        if (elenco[i]->grado <= atl.maxAI) {
            nuovo[j++] = elenco[i];
        }
    }
    el=j;
    temp=malloc(el*sizeof(ES));
    while(j<(NA+AA+AI)){
        nuovo[j]->grado=nuovo[j]->nE=nuovo[j]->inSol=-1;
        nuovo[j]->punti=nuovo[j]->rapp=-1;
        nuovo[j]->nome=NULL;
        j++;
    }
    for(i=0;i<el;i++){
        temp[i]=nuovo[i];
    }
    ordinamento(temp,el);
    for(i=0;i<el;i++){
        printf("%s %d %f\n",temp[i]->nome,temp[i]->grado,temp[i]->punti);
    }
    *n=el;
    return temp;
}

piano ** creaSolGreedy(ES **elenco,int esGara,int NA,int AA,int AI,int *bonus,atleta atl,float *point,int el){
    int i,grado=atl.maxSUM,pos=0,nuovo=1;
    float punteggio=0,bon=2.5;
    piano **sol=malloc(esGara*sizeof(*sol));
    for(i=0;i<esGara;i++){
        sol[i]=malloc(sizeof(piano));
    }
    for(i=0;i<esGara;i++){
        sol[i]->bonus=0;
        sol[i]->rip=0;
    }

    while(pos<esGara){
        for(i=0;i<el && pos<esGara;i++) {
            if(elenco[i]->rapp>0 && grado-elenco[i]->grado>=0){
                sol[pos]->id=elenco[i];
                elenco[i]->rapp--;
                if(elenco[i]->inSol==0){
                    punteggio+=elenco[i]->punti;
                    elenco[i]->inSol=1;
                    if(pos>0 && sol[pos-1]->id->nE!=sol[pos]->id->nE && bonus[0]==0){
                        sol[pos]->bonus=1;
                        punteggio+=bon;
                        bonus[0]=1;
                    }
                }
                else{
                    sol[pos]->rip=1;
                }
                pos++;
            }
        }
    }
    if((sol[pos-1]->id->nE==2 || sol[pos-1]->id->nE==3)&&(sol[pos-1]->bonus==0)&&(sol[pos-1]->id->grado>=5)){
        punteggio+=bon;
        bonus[1]=1;
    }
    *point=punteggio;
    return sol;
}


void stampaSol(ES **elenco,piano **sol,int esGara,int *bonus,float punteggio){
    int i;
    float punti;
    float bon[2]={0,0};
    printf("\n---------------PIANO DI GARA---------------\n\t(Sol.Greedy)\n");
    for(i=0;i<esGara;i++){
        if(sol[i]->rip==0) {
            printf("Punteggio:%.2f \t\tEsercizio: %s \n", sol[i]->id->punti,sol[i]->id->nome);
        }
        else{
            printf("Punteggio:0.00 \t\tEsercizio: %s \n", sol[i]->id->nome);
        }
    }
    if(bonus[0]==1) {
        bon[0] = 2.5;
    }
    if(bonus[1]==1){
        bon[1]=2.5;
    }
    printf("\nBONUS:\n\t-->Composizione: %.2f\n\t-->Uscita: %.2f\n",bon[0],bon[1]);
    printf("\n------> Punteggio totale: %.2f\n",punteggio);
}



