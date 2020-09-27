#include <stdio.h>
#include <stdlib.h>
#define MAXC 25
typedef struct s_prodotto{
    char nome[MAXC];
    float prezzo;
}prodotto;

prodotto * leggiFile(prodotto *lista,int *N);
int generaLista(prodotto *lista,int n,int k,float budget);
int comb_sempl(int pos,prodotto *sol,prodotto *val,int n,int k,float budget,int start,int count);

int main(){
    prodotto *lista;
    int n_prodotti,k,count;
    float budget;

lista=leggiFile(lista,&n_prodotti);
    printf("Inserisci il minimo numero di prodotti da acquistare: ");
    scanf("%d",&k);
    printf("Inserisci il budget: ");
    scanf("%f",&budget);
    count=generaLista(lista,n_prodotti,k,budget);
    printf("Numero di combinazioni trovate: %d\n",count);
return 0;
}

prodotto * leggiFile(prodotto *lista,int *N){
    int n,i=0;
    FILE *fp;
    if((fp=fopen("prodotti.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }
    fscanf(fp,"%d\n",&n);
    lista=(prodotto *)malloc(n*sizeof(prodotto));

    while((fscanf(fp,"%s %f\n",lista[i].nome,&lista[i].prezzo))!=EOF && i<n){
        i++;
    }
    fp=fclose(fp);
    *N=n;
    return lista;
}
int generaLista(prodotto *lista,int n,int k,float budget) {
    //modello del powerset con combinazioni semplici

    int i,count=0;
    for (i = k; i <= n; i++) {
        prodotto *sol = malloc(i * sizeof(prodotto));
        count=comb_sempl(0, sol, lista, n, i, budget,0,count);
    }
    return count;
}
int comb_sempl(int pos,prodotto *sol,prodotto *val,int n,int k,float budget,int start,int count){
    int i;
    float somma=0;
    if(pos>=k){
        somma=0;
        for(i=0;i<k;i++){
            somma+=sol[i].prezzo;
        }
        if(somma<=budget){
            printf("\t spesa:%.2f\t",somma);
            for(i=0;i<k;i++){
                printf("%s ",sol[i].nome);
            }
           printf("\n");
            count++;
        }
        return count;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        count=comb_sempl(pos+1,sol,val,n,k,budget,i+1,count);
    }
    return count;
}
