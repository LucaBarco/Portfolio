#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define M 25
#define N 200
typedef struct Occorrenza{
     int posizione;
	 char parola[M+1]; 
	 char chiave_rif[M+1];
} occorrenza;

typedef struct Chiavi{
     int n_caratteri;
	 char chiave[M+1];
	}chiavi;

int leggifile(FILE *fin1, chiavi sequenze[]);
int leggitesto(FILE *fin2, chiavi sequenze[],int n_sequenze,occorrenza occorrenze[]);
void stampaoccorrenze(occorrenza occorrenze[], int n_occorrenze,chiavi sequenze[],int n_sequenze);

int main(int argc, char *argv[]) {
	
	FILE* fin1,*fin2;
	chiavi sequenze[20]; //vettore di sequenze
	int n_sequenze=0,n_occorrenze=0;
	occorrenza occorrenze[500]; //vettore di occorrenze
	
		
 if((fin1=fopen("sequenze.txt","r"))==NULL){
 	printf("Errore nell'apertura del file!\n");
        }
	if((fin2=fopen("testo.txt","r"))==NULL){
		printf("Errore nell'apertura del file!\n'");
		}
	
	
	//lettura file sequenze
	n_sequenze=leggifile(fin1,sequenze);
	fclose(fin1);

	//lettura testo
	n_occorrenze=leggitesto(fin2,sequenze,n_sequenze,occorrenze);
	fclose(fin2);
	
	//stampa del vettore occorrenze 
	stampaoccorrenze(occorrenze,n_occorrenze,sequenze,n_sequenze);
	
	return 0;
}





int leggifile(FILE *fin1, chiavi sequenze[]){
	
	int i,k=0,n_sequenze=0;
	
		fscanf(fin1,"%d",&n_sequenze);	
		while((fscanf(fin1,"%s",sequenze[k].chiave))!=EOF && k<n_sequenze){
			sequenze[k].n_caratteri=strlen(sequenze[k].chiave);
			for(i=0;i<sequenze[k].n_caratteri;i++){
				sequenze[k].chiave[i]=toupper(sequenze[k].chiave[i]);
			}
	    k++;
		}
	return n_sequenze;
}

int leggitesto(FILE *fin2, chiavi sequenze[],int n_sequenze, occorrenza occorrenze[]){
	
	int i=0,j=0,cont_parole=0,n_occorrenze=0; //contatori
	int trovato=0,spaziatura=0;//flag -->il flag "spaziatura" serve per evitare che vengano contate stringhe composte da un solo spazio o da un a capo
	char parola_temp[M+1]; //stringa da analizzare
	
	
	
		i=0;
	while((fscanf(fin2,"%c",&parola_temp[i]))!=EOF){
		
		if(!isalnum(parola_temp[i])&&spaziatura==0){
			//creo la stringa da confrontare
			spaziatura=1;
			parola_temp[i]='\0';
			i=0;
			cont_parole++;
	
		//cerco eventuali occorrenze
			trovato=0;
				for(j=0;j<n_sequenze && trovato==0;j++){
			
				if((strncmp(parola_temp,sequenze[j].chiave,sequenze[j].n_caratteri))==0){
					
				occorrenze[n_occorrenze].posizione=cont_parole;
				strcpy(occorrenze[n_occorrenze].parola,parola_temp);
				strcpy(occorrenze[n_occorrenze].chiave_rif,sequenze[j].chiave);
				trovato=1;
				n_occorrenze++;
				}
		
	     	} 
			
	    }
		
		else{
			if(!isspace(parola_temp[i])&&!ispunct(parola_temp[i])){
			parola_temp[i]=toupper(parola_temp[i]);
			i++;
			spaziatura=0;
			}
		}				
					
	}
	return n_occorrenze;	
	
}


void stampaoccorrenze(occorrenza occorrenze[], int n_occorrenze,chiavi sequenze[],int n_sequenze){
	int i,k;
		printf("OCCORRENZE:\n");
		for(i=0;i<n_sequenze;i++){
			printf("\nChiave:%s\n",sequenze[i].chiave);
	for(k=0;k<n_occorrenze;k++){
		if(strcmp(sequenze[i].chiave,occorrenze[k].chiave_rif)==0){
		fprintf(stdout,"\t\t\tparola=%s\t\t\tposizione=%d\n",occorrenze[k].parola,occorrenze[k].posizione);
			}
		}	
	}
		return ;
}
