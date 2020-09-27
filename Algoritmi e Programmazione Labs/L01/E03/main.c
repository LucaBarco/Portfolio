#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define M 200

typedef struct riga{
	int n_car;
	char new_word[M];
}riga;

int leggifile(FILE* fin2, riga nrighe[]);
void scorrifile(FILE *fin1,FILE *fout,riga nrighe[],int n_sost);




int main(int argc, char *argv[]) {

	FILE* fin1,*fin2,*fout;
	riga nrighe[N];
	int n_sost;

	
	fin2=fopen("sost.txt","r");
	if(fin2!=NULL){
		printf("File sost.txt aperto correttamente!\n");
		}
	
	n_sost=leggifile(fin2,nrighe);
	
	fin2=fclose(fin2);
	
	fin1=fopen("src.txt","r");
	
	if(fin1!=NULL){
	printf("File src.txt aperto correttamente!\n");
	}
	
	fout=fopen("dest.txt","w");
	
	scorrifile(fin1,fout,nrighe,n_sost);
	
	fin1=fclose(fin1);
	fout=fclose(fout);
	
	
	return 0;
}


int leggifile(FILE* fin2, riga nrighe[]){
	int i,n_sost,status=0;
		fscanf(fin2,"%d\n",&n_sost);
	
	for (i=0;i<n_sost && status!=EOF;i++){
		status=fscanf(fin2,"%d %s\n",&nrighe[i].n_car,&nrighe[i].new_word);
		}
		
	return n_sost;
}



void scorrifile(FILE *fin1,FILE *fout,riga nrighe[],int n_sost){
	
		int i,status,l,trovato=0,v=0,punteggiat,passi=-1;
		char riga_temp[M+1];
		char* parola_temp; 
		char separatori[]={' ','\n'};
	
		while(fgets(riga_temp,M+1,fin1)!=NULL){
					parola_temp=strtok(riga_temp,separatori);
				//stampe per debug	
				//	printf("p=%d\n",passi++);
				//	printf("%s\n",parola_temp);
					while(parola_temp!=NULL){
		trovato=0;
		punteggiat=0;
		for(i=0;i<n_sost && trovato==0 && parola_temp!=NULL;i++){
			v=strlen(parola_temp);
		//	printf("%d\n",v);
			
			if(parola_temp[v-1]=='.'||parola_temp[v-1]==','||parola_temp[v-1]=='!'||parola_temp[v-1]=='?'||parola_temp[v-1]=='\n'){
				v--;
				punteggiat=1;
			}
				if(v==nrighe[i].n_car){
				fprintf(fout,"%s ",nrighe[i].new_word);
				
				if(punteggiat==1){			
					if(parola_temp[v]=='.'){
						fprintf(fout,".");
					
					}
				    	if(parola_temp[v]==','){
						fprintf(fout,",");
						
					}
						if(parola_temp[v]=='!'){
						fprintf(fout,"!");
					
					}
						if(parola_temp[v]=='?'){
						fprintf(fout,"?");
					
					}
						if(parola_temp[v]=='\n'){
						fprintf(fout,"\n");
					}
				}
					
				trovato=1;
				parola_temp=strtok(NULL,separatori);
			
			}
				
		}
		if(trovato==0){
		fprintf(fout,"%s ",parola_temp);
				parola_temp=strtok(NULL,separatori);
			
	}
	}
	if(parola_temp==NULL){
		fprintf(fout,"\n");
		}

	}
	return ;
}
