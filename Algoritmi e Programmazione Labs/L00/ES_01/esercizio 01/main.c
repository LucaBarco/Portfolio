#include <stdio.h>
#include <stdlib.h>
#define n 5
int main()
{

   char nomefile[15];
   int s_riga=0;
   int s_col[n]={0,0,0,0,0};
   float mediacol[n]={0,0,0,0,0};
   int n1=0,i;
   float media;
   int r[n]={0,0,0,0,0};
   FILE* fp;

   printf("Nome del file *.txt:");
   scanf("%s",nomefile);
   fp=fopen(nomefile,"r");
  // controllo printf("FILE APERTO!\n");

   while(fscanf(fp,"%d%d%d%d%d",&r[0],&r[1],&r[2],&r[3],&r[4])!=EOF){
        // controllo printf("%d %d %d %d %d\n",r[0],r[1],r[2],r[3],r[4]);
    for (i=0;i<n;i++){
        s_riga=s_riga+r[i];
        s_col[i]=s_col[i]+r[i];
    }
    media=((float)s_riga)/5;
    printf("Media riga %d:%.1f\n",n1+1,media);
    n1++;
    i=0;
    s_riga=0;

   }
   for (i=0;i<n1;i++){
    mediacol[i]=((float)s_col[i])/n1;
    printf("Media colonna %d:%.1f\n",i+1,mediacol[i]);
   }
   fclose(fp);
    return 0;
}
