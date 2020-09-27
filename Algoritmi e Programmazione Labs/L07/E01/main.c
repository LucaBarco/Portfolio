#include <stdio.h>
#include <stdlib.h>
#define MAXC 21
typedef struct city_s {
    char nome[MAXC];
    int popolo;
    int distanza;
    int *distanzemutue;
}city;

city * leggiFile(FILE *fp,city *v,int *n);
city * calcolaDistanzeMutue(city *v, int n);
void calcolaCity(city *v,int n,int k);
void combinazioniSemplici(int pos,int start,int n,int k,int *val,int *s,city *v,int *bests);
int controllaCity(int *s,int k,int n,city *v,int *bests);
int SommaDistanze(city *v,int *s,int n,int k);

int main(int argc,char *argv[]){
    city *elenco;
    int n,k;
    FILE *fp;
    if(argc<1){
        printf("Errore nell'inserimento dei parametri!\n");
        return 0;
    }
    fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return 0;
    }
    elenco=leggiFile(fp,elenco,&n);
    fp=fclose(fp);
    elenco=calcolaDistanzeMutue(elenco,n);
    printf("Inserire il numero di Autorita' di Ambito Territoriale Ottimato (ATO) da creare: ");
    scanf("%d",&k);
    calcolaCity(elenco,n,k);

    free(elenco);
    return 0;
}
city * leggiFile(FILE *fp,city *v,int *n){
    int N,i=0;
    fscanf(fp,"%d\n",&N);
    v=malloc(N*sizeof(city));
    while((fscanf(fp,"%s %d %d\n",v[i].nome,&v[i].popolo,&v[i].distanza))!=EOF && i<N){
        i++;
    }
    *n=N;
    return v;
}

city * calcolaDistanzeMutue(city *v, int n){

    int i,j;
    for(i=0;i<n;i++){
       v[i].distanzemutue=(int *)malloc(n*sizeof(int));
        for(j=0;j<n;j++){
            if(i==j){
               v[i].distanzemutue[j]=0;
            }
            else {
                if (j < i) {
                    v[i].distanzemutue[j] = v[i].distanza - v[j].distanza;
                }
                else {
                    v[i].distanzemutue[j] = v[j].distanza - v[i].distanza;
                }
            }
        }
    }

    return v;
}
void calcolaCity(city *v,int n,int k){

    int *s=malloc(k*sizeof(int));
    int *bests=malloc(k*sizeof(int));
    int *val=malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++){
        val[i]=i;
    }
    for(i=0;i<k;i++){
        bests[i]=i;
    }
    combinazioniSemplici(0,0,n,k,val,s,v,bests);
    printf("Soluzione migliore:%d\n",SommaDistanze(v,bests,n,k));
    for(i=0;i<k;i++){
        printf("\t%s\n",v[bests[i]].nome);
    }

}
void combinazioniSemplici(int pos,int start,int n,int k,int *val,int *s,city *v,int *bests){
    int i;
    if(pos>=k){
        if(controllaCity(s,k,n,v,bests)){
            for(i=0;i<k;i++){
                bests[i]=s[i];
            }
        }
        return;
        }
    for(i=start;i<n;i++){
        s[pos]=val[i];
        combinazioniSemplici(pos+1,i+1,n,k,val,s,v,bests);
    }
}
int controllaCity(int *s,int k,int n,city *v,int *bests){
    int sum1,sum2;
    sum1=SommaDistanze(v,s,n,k);
    sum2=SommaDistanze(v,bests,n,k);

    if(sum1<sum2){
        return 1;
    }
    return 0 ;
}

int SommaDistanze(city *v,int *s,int n,int k){
    int sum=0;
    int i=0,j;
    int atocontigue=0;
    int *distmin=malloc(n*sizeof(int));
    //i scorre il vettore soluzione, j scorre il vettore distmin e l'elenco v
    for(j=0;j<n;j++){
        if(j==s[i]&&i<k){
            distmin[j]=0;
            i++;
        }else{
            distmin[j]=-1;
        }
    }
    i=0;
    for(j=0;j<n;j++) {
        if(distmin[j]!=0) {
            atocontigue=0;
            if (i >= k - 1) {
                distmin[j] = v[j].distanzemutue[s[i]];
            } else {
                        if(v[j].distanzemutue[s[i]]<v[j].distanzemutue[s[i+1]]){
                            distmin[j]=v[j].distanzemutue[s[i]];
                        }
                else {
                            distmin[j] = v[j].distanzemutue[s[i + 1]];
                            i++;
                }
            }
        }
        else{
            if(atocontigue==1){
                i++;
            }
            if(atocontigue==0){
                atocontigue=1;
            }
        }
    }

    for(j=0;j<n;j++){
        sum=sum+v[j].popolo*distmin[j];
    }
    free(distmin);
    return sum;
}
