#include <stdio.h>
#include <stdlib.h>
#define MAX 30

int mediaMobile(int V[],int v,int k,float M[]);

int main(int argc, char *argv[]) {
	int V[MAX],k,v,l=0,s,cont=0;
	float M[MAX];
	
printf("Inserisci la dimensione del vettore: ");
scanf("%d",&l);
for(cont=0;cont<l;cont++){
	printf("Inserisci l'elemento %d: \n",cont+1);
	scanf("%d",&V[cont]);
}

printf("Inserire k: \n");
scanf("%d",&k);
s=mediaMobile(V,l,k,M);
for(cont=0;cont<s;cont++){
	printf("M[%d]=%.3f\n",cont+1,M[cont]);
}
	
	return 0;
}

int mediaMobile(int V[],int v,int k,float M[]){
	int i=0,j,somma=0;
	
	while(i<=v-k){
		somma=0;
		for(j=i;j<i+k;j++){
			somma=somma+V[j];
		}
		M[i]=((float)somma)/k;
		i++;
	}
	return i;
	
}
