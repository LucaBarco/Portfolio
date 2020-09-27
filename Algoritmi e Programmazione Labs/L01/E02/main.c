#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int mat_search(char mat[20][20],int r,int c,char s[20]);

int main(int argc, char *argv[]) {
	
	FILE* fp;
	char matrice[N][N],key[N],nomefile[N];
	int rig,col,i,j,cont;
	
	printf("Inserisci il nome del file:\n");
	scanf("%s",nomefile);
	if((fp=fopen(nomefile,"r"))!=NULL){
	
		fscanf(fp,"%d%d\n",&rig,&col);
	}
	
	//lettura matrice
	while(!feof(fp)){
		for(i=0;i<rig;i++){
			for(j=0;j<col;j++){
				fscanf(fp,"%c",&matrice[i][j]);
				
			}
			fscanf(fp,"%*c");
			
		}
	}
	fp=fclose(fp);

printf("Inserisci la chiave di ricerca: ");
scanf("%s",&key);
cont=mat_search(matrice,rig,col,key);
printf("La chiave e' contenuta %d volte",cont);
	
	return 0;
}

int mat_search(char mat[20][20],int r,int c,char s[20]){
	int i,j,f,l=0,linv,v,trovato=0,cont=0;
		v=strlen(s);
		
	for(i=0;i<r;i++){
		l=0;
		linv=v;
		for(j=0;j<c;j++){
			if(mat[i][j]==s[l]){
				l++;
				if(l>=v){
					cont++;
					l=0;
				}
		   	}
		   	else{
		   		l=0;
			   }
			
			if(mat[i][j]==s[linv]){
				linv--;
				if(linv<=0){
					cont++;
					linv=v;
				  }
		    	}
		    	else{
		    		linv=v;
				}
			}
	}
		
	f=cont;
		for(j=0;j<c;j++){
		l=0;
		linv=v;
		for(i=0;i<r;i++){
			if(mat[i][j]==s[l]){
				l++;
				
				if(l>=v){
					cont++;
					l=0;
				}
				}
				if(mat[i][j]==s[linv]){
					linv--;
				
				if(linv<=0){
					cont++;
					linv=v;
				  }
		    	}
			}
				
			}
			
return cont;
}
