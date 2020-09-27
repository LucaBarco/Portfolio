#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct atleta_s{
    int maxNA;
    int maxAA;
    int maxAI;
    int maxSUM;
}atleta;
typedef struct esercizio_s{
    char *nome;
    int grado;
    float punti;
    int inSol;

}ES;
typedef struct piano_s{
    int id;
    int elenco;
    int rip;
}piano;

void leggiFile(ES **elencoNA,ES** elencoAA,ES** elencoAI,FILE *fp,int NA,int AA,int AI);
atleta leggiAtleta();
float calcolaPunti(piano *sol,int esGara,ES **elencoNA,ES **elencoAA,ES **elencoAI,float *bon1,float *bon2);
int calcolaGrado(piano *sol,int esGara,ES **elencoNA,ES **elencoAA,ES **elencoAI);
void generaPiano(atleta x,ES **elencoNA,ES **elencoAA,ES **elencoAI,int NA,int AA,int AI,int esGara,float *punteggio);
void disp_rip(int pos,int *val,piano *sol,piano *bestsol,int NA,int AA,int AI,int esGara,atleta atl,ES **elencoNA,ES **elencoAA,ES **elencoAI,float *bestpoint,int *gradoTOT,float *bon1,float *bon2);
void stampaPiano(piano *sol,int n,float punteggio,ES **elencoNA,ES **elencoAA,ES **elencoAI,float bon1,float bon2);

int main() {
    ES **elencoNA,**elencoAA,**elencoAI;
    int NA,AA,AI,esGara=8,i;
    float punteggio;
    int *sol;
    FILE *fp;
    atleta atl;
    if((fp=fopen("elementi.txt","r"))==NULL){
        printf("Errore nell'apertura del file!\n");
    }
    fscanf(fp,"%d %d %d\n",&NA,&AA,&AI);
    elencoNA=malloc(NA*sizeof(*elencoNA));
    elencoAA=malloc(AA*sizeof(*elencoAA));
    elencoAI=malloc(AI*sizeof(*elencoAI));
    for(i=0;i<NA;i++){
        elencoNA[i]=malloc(sizeof(ES));
    }
    for(i=0;i<AA;i++){
        elencoAA[i]=malloc(sizeof(ES));
    }
    for(i=0;i<AI;i++){
        elencoAI[i]=malloc(sizeof(ES));
    }

    leggiFile(elencoNA,elencoAA,elencoAI,fp,NA,AA,AI);
    fclose(fp);
    atl=leggiAtleta();
    generaPiano(atl,elencoNA,elencoAA,elencoAI,NA,AA,AI,esGara,&punteggio);


    return 0;
}


void leggiFile(ES **elencoNA,ES** elencoAA,ES** elencoAI,FILE *fp,int NA,int AA,int AI){

    int i,finito=0;
    char nome[50];
    float punti;
    int grado;

    for(i=0;i<NA&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elencoNA[i]->punti=punti;
            elencoNA[i]->grado=grado;
            elencoNA[i]->nome = strdup(nome);
            elencoNA[i]->inSol=0;

        }
        else{
            finito=1;
        }
    }

    finito=0;
    for(i=0;i<AA&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elencoAA[i]->punti=punti;
            elencoAA[i]->grado=grado;
            elencoAA[i]->nome = strdup(nome);
            elencoAA[i]->inSol=0;

        }
        else{
            finito=1;
        }
    }
    finito=0;
    for(i=0;i<AI&&finito==0;i++){
        if((fscanf(fp,"%s %d %f",nome,&grado,&punti))!=EOF) {
            elencoAI[i]->punti=punti;
            elencoAI[i]->grado=grado;
            elencoAI[i]->nome = strdup(nome);
            elencoAI[i]->inSol=0;
        }
        else{
            finito=1;
        }
    }

}

atleta leggiAtleta(){
    atleta x;
    printf("\nInserire i dati dell'atleta!\n");
    printf("MAX difficolta' per esercizi NON ACROBATICI: ");
    scanf("%d",&x.maxNA);
    printf("MAX difficolta' per esercizi ACROBATICI AVANTI: ");
    scanf("%d",&x.maxAA);
    printf("MAX difficola' per esercizi ACROBATICI INDIETRO: ");
    scanf("%d",&x.maxAI);
    printf("MAX difficola' TOTALE: ");
    scanf("%d",&x.maxSUM);
    return x;
}

void generaPiano(atleta x,ES **elencoNA,ES **elencoAA,ES **elencoAI,int NA,int AA,int AI,int esGara,float *punteggio){
    //Modello combinatorio : disposizioni ripetute
    int *val=malloc((NA+AA+AI)*sizeof(int));
    piano *sol=malloc(esGara*sizeof(piano));
    piano *bestsol=malloc(esGara*sizeof(piano));
    int i,j;
    float bon1=0,bon2=0;
    float bestpoint=-10;
    int gradoTOT=0;
    for(i=0;i<NA;i++){
        val[i]=i;
    }
    for(i=NA,j=0;i<(NA+AA);i++,j++){
        val[i]=j;
    }
    for(i=(NA+AA),j=0;i<(NA+AA+AI);i++,j++){
        val[i]=j;
    }


    for(i=0;i<esGara;i++){
       sol[i].elenco=0;
        sol[i].rip=0;
    }
    disp_rip(0,val,sol,bestsol,NA,AA,AI,esGara,x,elencoNA,elencoAA,elencoAI,&bestpoint,&gradoTOT,&bon1,&bon2);
    *punteggio=bestpoint;
    stampaPiano(bestsol,esGara,bestpoint,elencoNA,elencoAA,elencoAI,bon1,bon2);
    return ;
}

void disp_rip(int pos,int *val,piano *sol,piano *bestsol,int NA,int AA,int AI,int esGara,atleta atl,ES **elencoNA,ES **elencoAA,ES **elencoAI,float *bestpoint,int *gradoTOT,float *bon1,float *bon2){
    int i,ripeti=0;
    float point=0;
    int inizio=0;
    if(pos>=esGara){
        point=calcolaPunti(sol,esGara,elencoNA,elencoAA,elencoAI,bon1,bon2);
        *gradoTOT=calcolaGrado(sol,esGara,elencoNA,elencoAA,elencoAI);
        if(point>*bestpoint && *gradoTOT<=atl.maxSUM){
            for(i=0;i<esGara;i++){
                bestsol[i].rip=sol[i].rip;
                bestsol[i].elenco=sol[i].elenco;
                bestsol[i].id=sol[i].id;
            }
            *bestpoint=point;
        }
        return;
    }

    for(i=0;i<NA;i++) {
        if (elencoNA[val[i]]->grado <= atl.maxNA) {
            sol[pos].id = val[i];
            sol[pos].elenco=1;
            if(elencoNA[val[i]]->inSol==0) {
                elencoNA[val[i]]->inSol=1;
                inizio=1;
            }
            else{
                sol[pos].rip=1;
                ripeti=1;
            }

            disp_rip(pos + 1, val, sol, bestsol, NA, AA, AI, esGara, atl, elencoNA, elencoAA, elencoAI, bestpoint, gradoTOT,bon1,bon2);

           if(ripeti==1){
                sol[pos].rip=0;
                ripeti=0;
            }
            if(elencoNA[val[i]]->inSol==1 && inizio==1){
                elencoNA[val[i]]->inSol=0;
                inizio=0;
            }

        }
    }
    inizio=0;

    for(i=NA;i<(NA+AA);i++){
        if(elencoAA[val[i]]->grado<=atl.maxAA) {
            sol[pos].id = val[i];
            sol[pos].elenco = 2;
            if(elencoAA[val[i]]->inSol==0) {
                elencoAA[val[i]]->inSol=1;
                inizio=1;
            }
            else{
                sol[pos].rip=1;
                ripeti=1;
            }
            disp_rip(pos + 1, val, sol, bestsol, NA, AA, AI, esGara, atl, elencoNA, elencoAA, elencoAI, bestpoint,gradoTOT,bon1,bon2);
            if(ripeti==1){
                sol[pos].rip=0;
                ripeti=0;
            }
            if(elencoAA[val[i]]->inSol==1 && inizio==1){
                elencoAA[val[i]]->inSol=0;
                inizio=0;
            }

        }
    }
    inizio=0;
    for(i=NA+AA;i<(NA+AA+AI);i++){
        if(elencoAI[val[i]]->grado<=atl.maxAI) {
            sol[pos].id = val[i];
            sol[pos].elenco = 3;

            if(elencoAI[val[i]]->inSol==0) {
                elencoAI[val[i]]->inSol=1;
                inizio=1;
            }
            else{
                sol[pos].rip=1;
                ripeti=1;
            }
            disp_rip(pos + 1, val, sol, bestsol, NA, AA, AI, esGara, atl, elencoNA, elencoAA, elencoAI, bestpoint,gradoTOT,bon1,bon2);
            if(ripeti==1){
                sol[pos].rip=0;
                ripeti=0;
            }
            if(elencoAI[val[i]]->inSol==1 && inizio==1){
                elencoAI[val[i]]->inSol=0;
                inizio=0;
            }
        }
    }

    return;
}
void stampaPiano(piano *sol,int n,float punteggio,ES **elencoNA,ES **elencoAA,ES **elencoAI,float bon1,float bon2){
    int i;
    float punti;
    printf("\n--------------- PIANO DI GARA ---------------\n");
    for(i=0;i<n;i++){
        switch(sol[i].elenco) {
            case 1:
                if(sol[i].rip==0){
                    punti=elencoNA[sol[i].id]->punti;
                }
                else{
                    punti=0;
                }
                printf("Punteggio:%.2f \t\tEsercizio:%.s\n",punti, elencoNA[sol[i].id]->nome);
                break;
            case 2:
                if(sol[i].rip==0){
                    punti=elencoAA[sol[i].id]->punti;
                }
                else{
                    punti=0;
                }
                printf("Punteggio:%.2f \t\tEsercizio:%.s\n",punti, elencoAA[sol[i].id]->nome);
                break;
            case 3:
                if(sol[i].rip==0){
                    punti=elencoAI[sol[i].id]->punti;
                }
                else{
                    punti=0;
                }
                printf("Punteggio:%.2f \t\tEsercizio:%.s\n", punti,elencoAI[sol[i].id]->nome);
                break;
        }
    }
    printf("Bonus:\n\tComposizione: %.2f\n\tUscita:%.2f\n",bon1,bon2);
    printf("Punteggio totale: %.2f\n",punteggio);
    printf("Grado totale: %d\n",calcolaGrado(sol,n,elencoNA,elencoAA,elencoAI));
}

float calcolaPunti(piano *sol,int esGara,ES **elencoNA,ES **elencoAA,ES **elencoAI,float *bon1,float *bon2){
    int bonus1=0,bonus2=1;
    float point=0,bonus=2.5;
    int i;

    for(i=0;i<esGara;i++){
        if(sol[i].rip==0) {
            if (sol[i].elenco == 1)
                point += elencoNA[sol[i].id]->punti;
            else if (sol[i].elenco == 2)
                point += elencoAA[sol[i].id]->punti;
            else if (sol[i].elenco == 3)
                point += elencoAI[sol[i].id]->punti;
        }
    }
    for(i=1;i<esGara && bonus1==0;i++){
        if(sol[i].elenco!=sol[i-1].elenco){
            point+=bonus;
            bonus1=1;
            *bon1=2.5;
            if(i==esGara-1){
                bonus2=0;
            }
        }
    }
    if(((sol[esGara-1].elenco==1 && elencoAA[sol[esGara-1].id]->grado>=5)  || (sol[esGara-1].elenco==2 && elencoAI[sol[esGara-1].id]->grado>=5))&&bonus2!=0){
        point+=bonus;
        *bon2=2.5;
    }
    return point;
}

int calcolaGrado(piano *sol,int esGara,ES **elencoNA,ES **elencoAA,ES **elencoAI){
    int i,grado=0;
    for(i=0;i<esGara;i++){
        switch(sol[i].elenco){
            case 1:
                grado+=elencoNA[sol[i].id]->grado;
                break;
                case 2:
                grado+=elencoAA[sol[i].id]->grado;
                break;
            case 3:
                grado+=elencoAI[sol[i].id]->grado;
                break;
        }
    }
    return grado;
}