#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXC 80


int leggiPagina(char pagina[][MAXC+1], int MAXR);
int riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int MAXP);
void InsertionSort(char *parole[],int np);
int confrontaParole(char *parola1,char *parola2);
int ricercaBinaria(char *parole[],int np,int l, int r, char cerca[]);


int main() {
    const int MAXR=60;
    const int MAXP=1000;
    char pagina[MAXR][MAXC+1];
    char *parole[MAXP];
    char *p;
    char cerca[MAXC+1],fine[]={'$','f','i','n','e','\0'};
    int nr,np;
    int find,find_sx,find_dx;
    int i,j,k;


    nr=leggiPagina(pagina,MAXR);
    np=riconosciParole(pagina,nr,parole,MAXP);
    InsertionSort(parole,np);
    p=pagina[0];



    printf("Inserisci la parola da cercare nel testo:\n\t(scrivi '$fine' per uscire)\n");
    scanf("%s",cerca);
    while(strcmp(cerca,fine)!=0) {

    //RICERCA OCCORRENZE
        find = ricercaBinaria(parole, np, 0, np, cerca);

        if (find != -1) {
            p = pagina[0];
            printf("Parola %s trovata in ", cerca);
            //CALCOLO INDICI DI RIGA E COLONNA NELLA MATRICE pagina 
            for (i = 0; i <= nr; i++) {
                for (j = 0; j < MAXC + 1; j++) {

                    if (parole[find] == p) {
                        printf("(%d,%d) ", i, j);
                    }
                    p++;
                }
            }

        //RICERCA DI OCCORRENZE MULTIPLE
            //RICERCA A DX DELLA PRIMA OCCORRENZA E RICERCA DI INDICI RIGA E COLONNA NELLA MATRICE pagina
            for(k=find+1;k<np;k++) {
                if (confrontaParole(parole[k], cerca) == 0) {
                    find_dx = k;
                    p=pagina[0];
                    for (i = 0; i <= nr; i++) {
                        for (j = 0; j < MAXC + 1; j++) {

                            if (parole[find_dx] == p) {
                                printf("(%d,%d) ", i, j);
                            }
                            p++;
                        }
                    }
                }
            }
            //RICERCA A SX DELLA PRIMA OCCORRENZA E RICERCA DI INDICI RIGA E COLONNA IN pagina
            for(k=find-1;k>=0;k--) {
                if (confrontaParole(parole[k], cerca) == 0) {
                    find_sx = k;
                    p=pagina[0];
                    for (i = 0; i <= nr; i++) {
                        for (j = 0; j < MAXC + 1; j++) {

                            if (parole[find_sx] == p) {
                                printf("(%d,%d) ", i, j);
                            }
                            p++;
                        }
                    }
                }
            }


            } else {
                printf("Parola non trovata!\n");
            }
            printf("\n");
            printf("Inserisci la parola da cercare nel testo:\n\t(scrivi '$ fine' per uscire)\n");
            scanf("%s", cerca);

        }

    return 0;
}

int leggiPagina(char pagina[][MAXC+1], int MAXR){

    FILE *fp;
    int i,j;


    if((fp=fopen("sequenze.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
        return 0;
    }

    for(i=0;i<MAXR &&(fgets(pagina[i],MAXC+1,fp)!=NULL) ;i++);

    fp=fclose(fp);
    i--; //dato che fgets fa un' iterazione in più

    return i;
}

int riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int MAXP){

    int i,j,np=0;
    int in_parola=1;

    for(i=0;i<=nr;i++){

        for(j=0;j<MAXC+1;j++){
                if((isalpha(pagina[i][j]))&&in_parola==1){
                parole[np]=&(pagina[i][j]);
                np++;
                in_parola=0;
                }
                else{
                    if((!isalpha(pagina[i][j]))&&in_parola==0){
                        in_parola=1;

                    }
                }
        }
    }
      return np;
}

void InsertionSort(char *parole[],int np){
    int i,j;
    char *x;
    for(i=1;i<np;i++){
       x=parole[i];
        j=i-1;

        while(j>=0 && confrontaParole(x,parole[j])<0){
            parole[j+1]=parole[j];
            j--;
        }
            parole[j+1]=x;

    }

}

int confrontaParole(char *parola1,char *parola2) {

    int k=0;
    char a,b;

    a=toupper(parola1[0]);
    b=toupper(parola2[0]);
     while(a==b&&isalpha(a)==1){
        k++;
        a=toupper(parola1[k]);
        b=toupper(parola2[k]);
    }
    if(isalpha(a)==0&&isalpha(b)==0){
        return 0;
    }
    else {
        return (a - b);
    }

}

int ricercaBinaria(char *parole[],int np,int l, int r, char cerca[]){
    int m;
    while(l<=r){
        m=l+(r-l)/2;

        if(confrontaParole(parole[m],cerca)==0){

            return m;
        }
        if(confrontaParole(parole[m],cerca)<0){

            l=m+1;
        }
        else{
            r=m-1;
        }
    }
    return -1;
}



