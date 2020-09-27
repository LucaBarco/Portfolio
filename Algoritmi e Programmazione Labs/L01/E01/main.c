#include <stdio.h>
#include <stdlib.h>
#define N 20

int intersezione(int v1[],int v2[],int v3[],int n,int m);
int unione(int v1[],int v2[],int v3[],int n,int m);
int differenza(int v1[],int v2[],int v3[],int n,int m);
int eliminaduplicati(int v1[],int dimv1);
void ordinamento(int v1[], int dim);
void stampa(int v[],int n);

int main(int argc, char *argv[]) {
	char read1[N+1],read2[N+1];
	int V1[N],V2[N],U[N+N],D[N],I[N];
	int i=0,temp,dim1=0,dim2=0,dimun,dimint,dimdiff;

	printf("Inserisci la dimensione del primo insieme:\n");
	scanf("%d",&dim1);
	printf("Inserisci gli elementi del primo insieme:\n");
	for (i=0;i<dim1;i++){
		scanf("%d",&V1[i]);
	}
	printf("Inserisci la dimensione del secondo insieme:\n");
	scanf("%d",&dim2);
	printf("Inserisci gli elementi del secondo insieme:\n");
	for (i=0;i<dim2;i++){
		scanf("%d",&V2[i]);
	}

	dimint=intersezione(V1,V2,I,dim1,dim2);
	dimun=unione(V1,V2,U,dim1,dim2);
	dimdiff=differenza(U,I,D,dimun,dimint);
	ordinamento(U,dimun);
    temp=eliminaduplicati(U,dimun);
    dimun=temp;
	ordinamento(I,dimint);
    temp=eliminaduplicati(I,dimint);
    dimint=temp;
	ordinamento(D,dimdiff);
    temp=eliminaduplicati(D,dimdiff);
    dimdiff=temp;
	printf("UNIONE: ");
	stampa(U,dimun);
	printf("DIFFERENZA: ");
	stampa(D,dimdiff);
	printf("INTERSEZIONE: ");
	stampa(I,dimint);

	return 0;
}

int intersezione(int v1[],int v2[],int v3[],int n,int m){
	//funzione che calcola l'insieme intersezione e ne restituisce la cardinalità
	int i=0,k=0,l=0,trovato=0;
	for (i=0;i<n;i++){
		trovato=0;
		for(k=0;k<m && trovato==0;k++){
			if (v1[i]==v2[k]){
				trovato=1;
				v3[l]=v1[i];
				l++;
			}
		}
	}

	return l;
}

int unione(int v1[],int v2[],int v3[],int n,int m){
	//funzione che calcola l'insieme unione e ne restituisce la cardinalità
	int i=0,j=0,trovato=0,l=n;

	for(i=0;i<n;i++){
		v3[i]=v1[i];
	}
		for(i=0;i<m;i++){
			trovato=0;
			for(j=0;j<n && trovato==0;j++){
				if(v3[j]==v2[i]){
					trovato=1;
				}

			}
			if(trovato==0){
				v3[l]=v2[i];
				l++;
			}
		}
	
		return l;
	}

int differenza(int v1[],int v2[],int v3[],int n,int m){
//funzione che calcola l'insieme differenza e ne restituisce la cardinalità
	int i=0,j=0,trovato=0,l=0;
	for (i=0;i<n;i++){
		trovato=0;
	for (j=0;j<m&&trovato==0;j++){
		if(v1[i]==v2[j]){
			trovato=1;
		}
	}
	if(trovato==0){
	v3[l]=v1[i]	;
	l++;}
	}

	return l;
}

int eliminaduplicati(int v1[],int dimv1){
	
	for(i=1;i<(dimv1);i++){
		if(v1[i]!=v1[i-1]){
		v1[j]=v1[i];
		j++;
		duplicati++;
		}

	}
	return duplicati+1;
}

void ordinamento(int v1[], int dim){
	//ordinamento tipo Insertion Sort
	int i,j,x;
	for(i=1;i<dim;i++){
		x=v1[i];
		j=i-1;
		while(j>=0 && x<v1[j]){
			v1[j+1]=v1[j];
			j--;
		}
	v1[j+1]=x;
	}
	return;
}

void stampa(int v[],int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d ",v[i]);
	}
	printf("\n");
	return;
}

