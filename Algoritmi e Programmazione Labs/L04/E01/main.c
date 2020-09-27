#include <stdio.h>
#define MAXR 50

int leggiMatrice(FILE *fp,int M[MAXR][MAXR],int *nr,int *nc);
int riconosciRegione(int M[MAXR][MAXR],int nr,int nc,int r,int c,int *b,int *h);
int main() {

    FILE *fp;
    int M[MAXR][MAXR];
    int nr,nc;
    int i,j,contaregioni=0;
    int b,h;

	//leggo matrice da file
    if((leggiMatrice(fp,M,&nr,&nc))==-1){
        return 0;
    }
	//ricerca di regioni
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
    if((riconosciRegione(M,nr,nc,i,j,&b,&h))==1){
        contaregioni++;
        printf("Regione %d: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d\n",contaregioni,i,j,b,h,b*h);
    }

        }
    }


    return 0;
}

int leggiMatrice(FILE *fp,int M[MAXR][MAXR],int *nr,int *nc){

    int i,j,status=0;
    int r,c;
    if((fp=fopen("matrice.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
        return -1;
    }
    fscanf(fp,"%d%d",nr,nc);

    for(i=0;i<*nr && status!=EOF;i++){
        for(j=0;j<*nc && status!=EOF;j++){
            status=fscanf(fp,"%d",&M[i][j]);
        }
    }
    fp=fclose(fp);
return 0;
}

int riconosciRegione(int M[MAXR][MAXR],int nr,int nc,int r,int c,int *b,int *h){

    int i,j;
    int base,altezza;

    int estremo=2,fineregione=0;
    if(M[r][c]==1) {
        estremo=1; //suppongo che sia un estremo  sup.sx e cerco eventuali contraddizioni
      
        if(!(r==0&&c==0)) {
            if (r == 0 && M[r][c - 1] != 0) {

                estremo = 0;
                return estremo;
            }
            if (c == 0 && M[r - 1][c] != 0) {
                estremo = 0;
                return estremo;

            }

            if (M[r - 1][c] != 0 || M[r][c - 1] != 0) {
                estremo = 0;
                return estremo;
            }
        }
	//se è un estremo,calcolo base e altezza della regione 
	//cerco le caselle nere nella riga e nella colonna passante per l'estremo, dato che si considerano solo regioni rettangolari
        base = 1;
        altezza = 1;
        i=r;
            for (j = c+1; j < nc && fineregione==0; j++) {
                if (M[i][j] == 1) {
                    base++;
                    M[i][j] = -1;
                }
                else{
                    fineregione=1;
                }
            }

        fineregione=0;
        j=c;
            for (i = r+1; i < nr &&fineregione==0 ; i++) {
                if (M[i][j] == 1) {
                    altezza++;
                    M[i][j] = -1;
                }
                else{
                    fineregione=1;
                }
            }
    }

    *b=base;
    *h=altezza;

    return estremo;
}
