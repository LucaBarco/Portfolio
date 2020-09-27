#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/*
i= indice per il vettore che tiene conto degli stati dei segnali
j= indice sfalsato indietro di uno per leggere due caselle "consecutive" in un buffer circolare
c=contatore per le verifiche ogni 2 segnali/ verifica uscita ogni 3 segnali uguali
*/
 int i=-1,v[3]={0};
void handler(int sig);


int main(){
signal(SIGUSR1,handler);
signal(SIGUSR2,handler);
int e=0,j=-2,c=0;
while(1){
	pause();
	j=(j+1)%3;
	c++;
	if(c==2){
		if(v[i]==v[j]){
			printf("Error!\n");
		e=v[j];
		}
		else{
			printf("Success!\n");
			c=0;
		}	
	}
	else{
	//c==3
	if(c==3 && v[i]==e){
		exit(1);	
	}	
	else{
	c=1;	
	}
	}
	
}
return 0;
}

void handler(int sig){
i=(i+1)%3;
	if(sig==SIGUSR1){
	v[i]=1;
	}
	else if(sig==SIGUSR2){
	v[i]=2;
	}

}
