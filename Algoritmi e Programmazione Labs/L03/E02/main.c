#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 31
#define MAXN 100


typedef struct voloaereo{
	char codice[N];
	char partenza[N];
	char destinazione[N];
	char dataeora[N];
	char vettore[N];
	
}voloaereo;
typedef enum{
	r_date,
	r_origine,
	r_destinazione,
	r_vettore,
	r_fine
}comando_e;


int leggiTabella(FILE *fp,voloaereo volo[]);
int leggicomando();
void selezionaDati(voloaereo volo[],int n_voli,comando_e comando);
void cercadate(voloaereo volo[],int n_voli,char data1[],char data2[]);
void cercapartenze(voloaereo volo[],int n_voli,char partenza_key[]);
void cercaarrivi(voloaereo volo[],int n_voli,char destinazione_key[]);
void cercavettore(voloaereo volo[],int n_voli,char vettore_key[]);



int main(int argc, char *argv[]) {
	FILE *fp;
	comando_e comando;
	voloaereo volo[MAXN];
	int n_voli;
	
	n_voli=leggiTabella(fp,volo);
	comando=leggicomando();
	selezionaDati(volo,n_voli,comando);
	
	
	
	return 0;
}

int leggiTabella(FILE *fp,voloaereo volo[]){
	
	int i=0,n_dati=0;
	fp=fopen("voli.txt","r");
	fscanf(fp,"%d",&n_dati);
	while((fscanf(fp,"%s %s %s %s %s",volo[i].codice,volo[i].partenza,volo[i].destinazione,volo[i].dataeora,volo[i].vettore))!=EOF){
	n_dati++;
	i++;
}
fp=fclose(fp);
/*for(i=0;i<n_dati;i++){
	printf("%s %s %s %s %s\n",volo[i].codice,volo[i].partenza,volo[i].destinazione,volo[i].dataeora,volo[i].vettore);
}*/ //DEBUG
return n_dati;
	
}

int leggicomando(){
	char tabella[5][N]={ "date","origine","destinazione","vettore","fine"};
	char s[N];
	int c=0;
	printf("Inserisci il comando:\n\tdate\t(mostra voli partiti in un intervallo di date)\n\torigine\t(mostra voli partiti da una localita')\n\tdestinazione\t(mostra voli arrivati in una localita')\n\tvettore\t(mostra localita' di partenza dei voli con quel vettore)\n\tfine\n");
	scanf("%s",s);
	
	while(c<4 &&strcmp(s,tabella[c])!=0){
		c++;
	}
	return c;
}
void selezionaDati(voloaereo volo[],int n_voli,comando_e comando){
	
	char data1[MAXN],data2[MAXN];
	char partenza_key[MAXN],destinazione_key[MAXN],vettore_key[MAXN];
	

	switch(comando){
		case r_date:
			printf("Inserisci la prima data\n\t(formato YYYY/MM/DD)\n");
			scanf("%s",data1);
			printf("Inserisci la seconda data\n\t(formato YYYY/MM/DD)\n");
			scanf("%s",data2);
			cercadate(volo,n_voli,data1,data2);
			break;
		case r_origine:
			printf("Inserisci la localita' di partenza da ricercare:");
			scanf("%s",partenza_key);
			cercapartenze(volo,n_voli,partenza_key);
			break;
		case r_destinazione:
			printf("Inserisci la localita' di arrivo da ricercare:");
			scanf("%s",destinazione_key);
			cercaarrivi(volo,n_voli,destinazione_key);
			break;
		case r_vettore:
			printf("Inserisci il vettore da ricercare:");
			scanf("%s",vettore_key);
			cercavettore(volo,n_voli,vettore_key);
			break;
		case r_fine:
			return;
			break;
		default:
			printf("Comando errato!\n");
			break;
	}
	return;
}

void cercadate(voloaereo volo[],int n_voli,char data1[],char data2[]){
//elenca i voli partiti in un certo intervallo di date
	int i,trovato=0;
	for(i=0;i<n_voli;i++){
	
	
if(strcmp(volo[i].dataeora,data1)>0 && (strcmp(volo[i].dataeora,data2)<0)){
	printf("%s\n",volo[i].codice);
	trovato=1;
}

if(trovato==0){
	printf("Nessuna occorrenza trovata\n");
}
}
return;
}

void cercapartenze(voloaereo volo[],int n_voli,char partenza_key[]){
	//elenca i voli partiti da una cerca località
	int i,trovato=0;
	for(i=0;i<n_voli;i++) {
		if((strcmp(volo[i].partenza,partenza_key))==0){
			printf("%s\n",volo[i].codice);
			trovato=1;
		}
	}
	if(trovato==0){
	printf("Nessuna occorrenza trovata\n");
}
	
return;
}
void cercaarrivi(voloaereo volo[],int n_voli,char destinazione_key[]){
	//elenca i voli diretti verso una certa località
	int i,trovato=0;
	for(i=0;i<n_voli;i++) {
		if((strcmp(volo[i].destinazione,destinazione_key))==0){
			printf("%s\n",volo[i].codice);
			trovato=1;
		}
	}
	if(trovato==0){
	printf("Nessuna occorrenza trovata\n");
}
return;
}

void cercavettore(voloaereo volo[],int n_voli,char vettore_key[]){
	//elenca tutte le località da cui sia decollato almeno un volo con quel vettore
	
int i,trovato=0;
for(i=0;i<n_voli;i++) {
		if((strcmp(volo[i].vettore,vettore_key))==0){
		
			printf("%s\n",volo[i].partenza);
			trovato=1;
		
		}
	}
if(trovato==0){
	printf("Nessuna occorrenza trovata\n");
}

return;	
}
