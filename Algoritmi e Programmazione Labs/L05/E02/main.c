#include <stdio.h>
#define N 2
#define MAXS 11

typedef struct item_s{
    int a,b;
    char c;
    float d;
    char s[MAXS];
    }Item;

void leggiFile(FILE *fp, Item M[][N]);

int main() {
   Item M[N][N];
    FILE *fp;
    int r,c;
    leggiFile(fp,M);
    printf("Inserisci gli indici di riga e colonna: ");
    scanf("%d%d",&r,&c);
    while(r>=0&&r<=N-1&&c>=0&&c<=N-1){
        printf("Contenuto M[%d][%d]:\n",r,c);
        printf("\tContenuto \tPuntatore\n");
               printf("\t%d \t\t%p\n\t%d \t\t%p\n\t%c \t\t%p\n\t%f \t%p\n\t%s \t\t%p\n",M[r][c].a,&M[r][c].a,M[r][c].b,&M[r][c].b,M[r][c].c,&M[r][c].c,M[r][c].d,&M[r][c].d,M[r][c].s,&M[r][c].s);
        printf("Inserisci gli indici di riga e colonna: ");
        scanf("%d%d",&r,&c);
    }
  printf("----------Indici non validi!----------\n");
  printf("----------Fine iterazioni!----------\n");
    return 0;
}

void leggiFile(FILE *fp, Item M[][N]){

    int i,j,status=0;
    if((fp=fopen("testo.txt","r"))==NULL){
        printf("Errore nell'apertura del file!");
        return;
    }
    for(i=0;i<N && status!=EOF;i++){
        for(j=0;j<N && status!=EOF;j++){
            status=fscanf(fp,"%d%d %c%f%s",&M[i][j].a,&M[i][j].b,&M[i][j].c,&M[i][j].d,&M[i][j].s);
        }
    }
    fp=fclose(fp);
    return ;
}