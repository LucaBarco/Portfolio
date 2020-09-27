#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int contcons(char parola[],int m);
int main(int argc, char *argv[]) {
	int consp=0,cons=0;
	int N,m=21,l=11,i=0;
	char P[m],parola[m],filein[l],fileout1[l],fileout2[l];
	FILE *fpin,*fpout1,*fpout2;
	
	printf("Inserisci il nome del file da aprire:\n");
	scanf("%s",filein);
	printf("Nome file ordine alfabetico:\n");
	scanf("%s",fileout1);
	printf("Nome file conteggio consonanti:\n");
	scanf("%s",fileout2);
	
/*	if(fpin=fopen(filein,"r")==NULL){
		printf("Errore nell'apertura del file!\n'");
		return 0;
	}
	
		if(fpout1=fopen(fileout1,"w")==NULL){
		printf("Errore nell'apertura del file!\n'");
		return 0;
	}
	
	if(fpout2=fopen(fileout2,"w")==NULL){
		printf("Errore nell'apertura del file!\n'");
		return 0;
	}*/
	fpin=fopen(filein,"r");
	fpout1=fopen(fileout1,"w");
	fpout2=fopen(fileout2,"w");
	
	fscanf(fpin,"%d %s\n",&N,P);
	consp=contcons(P,m);
	printf("%s %d\n",P,consp);
	while(fscanf(fpin,"%s\n",parola)!=EOF){
		//printf("passo 1\n");
		printf("%d",contcons(parola,m));
		if(consp<contcons(parola,m)){
			//printf("passo 2\n");
			fprintf(fpout1,"%s\n",parola);
		}
		if(strcmp(parola,P)>0){
		//	printf("passo 3\n");
			fprintf(fpout2,"%s\n",parola);
		}
	i++;	
	}
	fclose(fpin);
	fclose(fpout1);
	fclose(fpout2);
	return 0;
}

int contcons(char parola[],int m){
	int i=0,finito=0,consonanti=0;
	for(i=0;i<strlen(parola) && finito==0;i++){
		if(parola[i]=='\0'){
			finito=1;
		}
		if(parola[i]=='a'||parola[i]=='e'||parola[i]=='i'||parola[i]=='o'||parola[i]=='u'){
		}
		else{
				consonanti++;
		}
		
	}
	return consonanti;
}
