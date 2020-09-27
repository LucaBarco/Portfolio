#include <stdio.h>
#include <stdlib.h>
#define N 20

void leggimatrice(FILE *fin,int matrice[N][N],int dimmatr[]);
void stampasottomatrici(int matrice[N][N],int dimmatr[]);
int main(int argc, char *argv[]) {
	
	FILE* fin;
	int matrice[N][N];
	int dimmatr[2],r,c,status=2,somma=0,i,j;
	
	
	if((fin=fopen("matrice.txt","r"))==NULL){
		printf("Errore nell'apertura del file!\n");
		return 0;
	}
	leggimatrice(fin,matrice,dimmatr);
	fin=fclose(fin);
	
	stampasottomatrici(matrice,dimmatr);
	
	

return 0;
}


void leggimatrice(FILE *fin,int matrice[N][N],int dimmatr[]){
	int i,j,status=0;
		fscanf(fin,"%d %d",&dimmatr[0],&dimmatr[1]);
	
for(i=0;i<dimmatr[0] && status!=EOF;i++){
	for(j=0;j<dimmatr[1] && status!=EOF;j++){
		status=fscanf(fin,"%d",&matrice[i][j]);
	}
}
return;
}
void stampasottomatrici(int matrice[N][N],int dimmatr[]){
	int i,j,r,c,somma=0;
	
	printf("Inserisci gli indici di riga e colonna:\n");
	scanf("%d %d",&r,&c);
	
	while(!(r<0||c<0||r>dimmatr[0]||c>dimmatr[1])){
	
	//sottomatrice nord-ovest	
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			somma+=matrice[i][j];
		}
	}
	printf("NO= %d\n",somma);
	somma=0;
	
	//sottomatrice nord-est
	for(i=0;i<r;i++){
		for(j=c+1;j<dimmatr[1];j++){
			somma+=matrice[i][j];
		}
	}
	printf("NE= %d\n",somma);
	somma=0;
		
	//sottomatrice sud-ovest
	for(i=r+1;i<dimmatr[0];i++){
		for(j=0;j<c;j++){
			somma+=matrice[i][j];
		}
	}
	printf("SO= %d\n",somma);
	somma=0;
	
	//sottomatrice sud-est
	for(i=r+1;i<dimmatr[0];i++){
		for(j=c+1;j<dimmatr[1];j++){
			somma+=matrice[i][j];
		}
	}
	printf("SE= %d\n",somma);
	somma=0;
	
	printf("Inserisci gli indici di riga e colonna:\n");
	scanf("%d %d",&r,&c);
	}
	
return;
}

