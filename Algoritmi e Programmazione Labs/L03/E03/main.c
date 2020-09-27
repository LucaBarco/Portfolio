#include <stdio.h>
#include <math.h>
#define N 50

void leggiMatrice(FILE *fp,char matrice[N][N],int dimmatr[]);
void verificaCammino(FILE *fin,char matrice[N][N],int dimmatr[]);
int main(int argc, char *argv[]) {
    FILE *fp,*fin;
    char matrice[N][N];
    int dimmatr[2];



    if(argc<3){
        printf("Errore! Numero parametri non valido!\n");
        return 0;
    }
    if((fp=fopen(argv[1],"r"))==NULL){
        printf("Errore nell'apertura del file contenente la matrice!\n");
        }

    leggiMatrice(fp,matrice,dimmatr);
    fp=fclose(fp);
    if((fin=fopen(argv[2],"r"))==NULL){
        printf("Errore nell'apertura del file contenente il cammino!\n");
    }
    verificaCammino(fin,matrice,dimmatr);


    return 0;
}

void leggiMatrice(FILE *fp,char matrice[N][N],int dimmatr[]){

    int i,j,status=0;
    fscanf(fp,"%d%d\n",&dimmatr[0],&dimmatr[1]);
    for(i=0;i<dimmatr[0]&&status!=EOF;i++){
        for(j=0;j<dimmatr[1]&&status!=EOF;j++){
            status=fscanf(fp,"%c",&matrice[i][j]);
        }
        fscanf(fp,"\n");
    }
    //printf("Matrice letta con successo!\n");
    for(i=0;i<dimmatr[0];i++){
        for(j=0;j<dimmatr[1];j++){
           printf("%c",matrice[i][j]);
        }
        printf("\n");
    }

    return;
}




void verificaCammino(FILE *fin,char matrice[N][N],int dimmatr[]){


    int i = 0, j = 0, H, V, k, p, contapassi = 0;
    int continua = 0, semplice = 0,finito=0;


    while ((fscanf(fin, "%d%d", &H, &V)) != EOF && finito==0) {

        printf("i=%d j=%d\n", i, j);
        printf("%d %d\n", H, V);
        V = -1 * V;
        printf("Nuovo V:%d\n", V);
        printf("indici di arrivo col:%d rig:%d\n", H + j, V + i);
        continua = 0;
        if (i + V > dimmatr[0] || j + H > dimmatr[1] || i + V < 0 || j + H < 0) {
            printf("Cammino al di fuori della matrice!\n");
            return;
        }
        if (H > 0 && V == 0) {
            //scorro vs destra
            for (p = j; p < j + H && continua == 0; p++) {
                if (matrice[i][p] == '-' || matrice[i][p] == 'I') {
                    matrice[i][p]='o';
                    contapassi++;
                }
                else {
                    if (matrice[i][p] == 'o') {
                        semplice = 1;
                        contapassi++;
                    }
                    else {
                        continua = 1;
                    }
                }
            }
            j = p;
        }
        if (H < 0 && V == 0) {
            //scorro vs sinistra
            for (p = j; p > j + H && continua == 0; p--) {
                if (matrice[i][p] == '-' || matrice[i][p] == 'I') {
                    contapassi++;
                    matrice[i][p]='o';
                } else {
                    if (matrice[i][p] == 'o') {
                        semplice = 1;
                        contapassi++;
                    }
                    else {
                        continua = 1;
                    }
                }
            }
            j = p;
        }
        if (H == 0 && V > 0) {
            //scorro vs basso
            for (k = i; k < i + V && continua == 0; k++) {
                if (matrice[k][j] == '-' || matrice[k][j] == 'I') {
                    contapassi++;
                    matrice[k][j]='o';
                } else {
                    if (matrice[k][j] == 'o') {
                        semplice= 1;
                        contapassi++;
                    }
                    else {
                        continua = 1;
                    }
                }
            }
            i = k;
        }


        if (H == 0 && V < 0) {
            //scorro vs alto
            for (k = i; k > i + V && continua == 0; k--) {
                if (matrice[k][j] == '-' || matrice[k][j] == 'I') {
                    contapassi++;
                    matrice[k][j]='o';
                } else {
                    if (matrice[k][j] == 'o') {
                        semplice= 1;
                        contapassi++;
                    }
                    else {
                        continua = 1;
                    }
                }
            }
            i = k;
        }



    }
    if (matrice[i][j]=='U') {
        if(semplice==0) {
            printf("Trovato cammino semplice!\n\tLunghezza:%d\n", contapassi);
        }
        if (semplice==1){
            printf("Trovato cammino non semplice!\n\tLunghezza:%d\n", contapassi);
        }
    }
return ;
}




