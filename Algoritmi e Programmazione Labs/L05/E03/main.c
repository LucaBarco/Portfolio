#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 11
typedef struct scelta{
    char *scelte;
    int n_scelte;
}Livello;

Livello * leggiFile(FILE *fp,Livello *val,int *n);
void generaSigle(int pos,Livello *val, char *sol, int n,FILE *fout);
int main()
{
    FILE *fp,*fout;
    Livello *val;
    int n_car,i=0;
    char *sol;
    int pos=0;
    if((val=leggiFile(fp,val,&n_car))==-1){
        return 0;
    }

    sol=(char *)malloc((n_car+1)*sizeof(char));

    if((fout=fopen("output.txt","w"))==NULL){
        printf("Errore nell'apertura del file!\n");
        return 0;
    }
    generaSigle(pos,val,sol,n_car,fout);
    fout=fclose(fout);
    printf("----------Scrittura su file eseguita!----------");

    for(i=0;i<n_car;i++){
        free(val[i].scelte);
    }
    free(val);
    free(sol);
    return 0;
}

Livello * leggiFile(FILE *fp,Livello *val,int *n){

    int j=0,i,l;
    char stringa_temp[MAXC];

    if((fp=fopen("sigle.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&i);
    *n=i;
    val=(Livello *)malloc(i*sizeof(Livello));
    while(fscanf(fp,"%s",stringa_temp)!=EOF&&j<3){
        l=strlen(stringa_temp);
        val[j].n_scelte=l;
        val[j].scelte=malloc((l+1)*sizeof(char));
        strcpy(val[j].scelte,stringa_temp);
        j++;
    }
    fp=fclose(fp);
    return val;
}

void generaSigle(int pos,Livello *val, char *sol, int n,FILE* fout){

    int i;
    if(pos>=n){
        sol[pos]='\0';
        fprintf(fout,"%s\n",sol);
        return;
    }
    for(i=0;i<val[pos].n_scelte;i++){
        sol[pos]=val[pos].scelte[i];
        generaSigle(pos+1,val,sol,n,fout);

    }
    return;
}