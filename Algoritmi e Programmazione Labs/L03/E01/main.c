#include <stdio.h>
#include <stdlib.h>
#define N 50
void leggimatrice(FILE *fp, int matrice[N][N],int dimmatr[]);
void cercaregioni(int matrice[N][N], int dimmatr[]);
int main()
{
   FILE *fp;
   int matrice[N][N],dimmatr[2];
   
   int i,j,a,b,p,k,status,conta_regioni=0,coor_x,coor_y,base_r,altezza_r;
   int trovato=0,continua=1,continuarighe=1,continuacolonne=1,bordor=0,bordoc=0;


   fp=fopen("matrice.txt","r");
	leggimatrice(fp,matrice,dimmatr);
   	fp=fclose(fp);

	cercaregioni(matrice,dimmatr);

    return 0;
}

void leggimatrice(FILE *fp, int matrice[N][N],int dimmatr[]){
int i,j,status=0;
fscanf(fp,"%d%d\n",&dimmatr[0],&dimmatr[1]);

   for(i=0;i<dimmatr[0] && status!=EOF;i++){
    for(j=0;j<dimmatr[1] && status!=EOF;j++){
        status=fscanf(fp,"%d",&matrice[i][j]);
    }
   }
   return;
}

void cercaregioni(int matrice[N][N], int dimmatr[]){
	int nr,nc; //parametri matrice
	int i,j,a,b,p,k;
	int conta_regioni=0;//contatore
	int coor_x,coor_y,base_r,altezza_r; //valori caratterizzanti della regione
   int trovato=0,continua=1,continuarighe=1,continuacolonne=1,bordor=0,bordoc=0; //flag
   
   nr=dimmatr[0];
   nc=dimmatr[1];
   //scorro la matrice. Quando trovo 1, cerco nelle altre direzioni altre caselle contenenti 1
	 for(i=0;i<nr;i++){
     for(j=0;j<nc;j++){
        if(matrice[i][j]==1){
                coor_x=i;
                coor_y=j;
                conta_regioni++;
                base_r=0;
                altezza_r=0;
           		k=j;
           		p=i;
            	continuacolonne=1;
            	continuarighe=1;
            	continua=1;
            	
            while(k<nc&&p<nr&&continua==1){
                if(k==nc-1&&continuarighe==1){ 
				base_r++;               			       
                continuarighe=0;
                
				}
				else{  
                if(matrice[i][k]==1&&continuarighe==1){
                    base_r++;
                    k++;
                }
                else{
                	continuarighe=0;
					}
				}
		
				if(p==nr-1&&continuacolonne==1){
				altezza_r++;
					continuacolonne=0;
				}
				else{
                if(matrice[p][j]==1&&continuacolonne==1){
                    altezza_r++;
                    p++;
                }
                else{
                	continuacolonne=0;
					}
				}
	
				if(continuacolonne==0&&continuarighe==0){
					continua=0;
				}  
            }

            if(continua==0){
           for(a=i;a<i+altezza_r;a++){
                for(b=j;b<j+base_r;b++){
                    matrice[a][b]=0;
                }
            }
            printf("Regione %d: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d\n",conta_regioni,coor_x,coor_y,base_r,altezza_r,base_r*altezza_r);
            trovato=0;
            bordor=0;
            bordoc=0;
   	
            }
        }
    }
   }
	
	return;
	
}
