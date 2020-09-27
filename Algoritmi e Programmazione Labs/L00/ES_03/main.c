#include <stdio.h>
#include <stdlib.h>
#define N 11

float valutaHorner(float P[N], float x);

int main(int argc, char *argv[]) {
	float c[N];
	int grado,M,i;
	float a,b,h,sommatoria=0,integrale=0;
	
	printf("Inserisci il grado del polinomio:");
	scanf("%d",&grado);
		printf("Inserisci i coefficenti polinomio:");
	for (i=0;i<grado+1;i++){
		scanf("%f",&c[i]);
	}
	printf("Inserisci gli estremi di integrazione e il numero di sottointervalli:");
	scanf("%f %f %d",&a,&b,&M);
	
	h=(b-a)/M;
	
	for(i=0;i<M;i++){	
	
	sommatoria=sommatoria+valutaHorner(c,(a+i*h+h/2));

	}
	integrale=h*sommatoria;
	printf("Integrale:%f\n",integrale);
	return 0;
}

float valutaHorner(float P[N], float x){
	int i;
	float somma=P[N-1];
	for (i=N-1;i>0;i--){
	somma=somma*x+P[i-1];
}
	return somma;	
	}


