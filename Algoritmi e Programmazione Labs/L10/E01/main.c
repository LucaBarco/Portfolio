#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct target{
    int x;
    int y;
    int val;
}target_c;

typedef struct target_vect{
    target_c *elenco;
    int n;
}Target;

typedef struct risorsa{
    int r;
    int a;
    int d;
    int c;
    int occ;
    int id;
}Risorsa_c;

typedef struct risorsa_vect{
    Risorsa_c *elenco;
    int n;
}Risorsa;


Target leggiFileTarget(FILE *fp, Target a);
Risorsa leggiFileRisorsa(FILE *fp,Risorsa r);
int **inizializzaMappa(int nr,int nc,Target all);
int calcolaOccorrenze(Risorsa el,Target all,Target nem,int budget);
void calcolaElenchi(Risorsa el,int budget,int n,Target all,Target nem,int nr,int nc);
void comb_rip(int pos,int start,int k,Risorsa val,Risorsa sol,int *count,int budget,int spesacorr,Target all,Target nem,int nr,int nc,int *finito);
void disp_semplici(int *posizioni,Risorsa val,int nc,int nr,int *finito,int **MappaAll,int **MappaNem,int insert);
int controllaSol(int *posizioni,int **MappaAll,int **MappaNem,int nr,int nc,Risorsa val);
void stampaSol(Risorsa val, int *posizioni,int nr);
int provaElenco(Risorsa sol,Target all,Target nem,int nr,int nc);


int main(int argc, char **argv) {
    FILE *fpa,*fpn,*fpr;
    Target alleati;
    Target nemici;
    Risorsa lista;
    int nr,nc,budget,maxocc,res;

    if(argc<3){
        printf("Errore nell'inserimento dei parametri!\n");
        return -1;
    }
    nr=atoi(argv[1]);
    nc=atoi(argv[2]);
    budget=atoi(argv[3]);
    fpa=fopen("alleati.txt","r");
    fpn=fopen("nemici.txt","r");
    fpr=fopen("risorse.txt","r");
    if(fpa==NULL||fpn==NULL||fpr==NULL){
        return -1;
    }
    alleati=leggiFileTarget(fpa,alleati);
    nemici=leggiFileTarget(fpn,nemici);
    lista=leggiFileRisorsa(fpr,lista);
    fclose(fpa);
    fclose(fpn);
    fclose(fpr);
    maxocc=calcolaOccorrenze(lista,alleati,nemici,budget);
    calcolaElenchi(lista,budget,maxocc,alleati,nemici,nr,nc);

    return 0;
}
Target leggiFileTarget( FILE *fp,Target a){
    int N,i=0;
    fscanf(fp,"%d\n",&N);
    a.n=N;
    a.elenco=malloc(N*sizeof(*a.elenco));
    while(fscanf(fp,"%d %d %d",&a.elenco[i].x,&a.elenco[i].y,&a.elenco[i].val)!=EOF){
        i++;
    }
    return a;
}

Risorsa leggiFileRisorsa(FILE *fp,Risorsa r){
    int N,i=0;
    fscanf(fp,"%d\n",&N);
    r.n=N;
    r.elenco=malloc(N*sizeof(*r.elenco));
    while(fscanf(fp,"%d %d %d %d",&r.elenco[i].r,&r.elenco[i].a,&r.elenco[i].d,&r.elenco[i].c)!=EOF){
        r.elenco[i].occ=1;
        r.elenco[i].id=i;
        i++;
    }
    return r;
}

int **inizializzaMappa(int nr,int nc,Target all){
    //0: caselle vuote
    //num. negativo=casella occupata dal target
    int **mappa=malloc(nr*sizeof(int *));
    int i,j;
    for(i=0;i<nr;i++){
        mappa[i]=malloc(nc*sizeof(int));
    }
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++)
            mappa[i][j]=0;
    }
    for(i=0;i<all.n;i++){
        mappa[all.elenco[i].x][all.elenco[i].y]=-all.elenco[i].val;
    }
    return mappa;
}

int calcolaOccorrenze(Risorsa el,Target all,Target nem,int budget){
    int i,max=0;
    for(i=0;i<el.n;i++){
        el.elenco[i].occ=budget/el.elenco[i].c;
        if(el.elenco[i].occ>max){
            max=el.elenco[i].occ;
        }
    }
    return max;
}
void calcolaElenchi(Risorsa el,int budget,int n,Target all,Target nem,int nr,int nc){
    Risorsa vuoto;
    vuoto.n=0;
    vuoto.elenco=NULL;
   // link head=NEW(vuoto,NULL);
   // link t;
    int i,j,count=0,spesacorr=0,finito=0;
    Risorsa nuovo;
    i=1;
    while(i<=n){
       // head=NEW(vuoto,NULL);
        count=0;
        nuovo.elenco=malloc(i*sizeof(*nuovo.elenco));
        nuovo.n=i;
        comb_rip(0,0,i,el,nuovo,&count,budget,spesacorr,all,nem,nr,nc,&finito);
        /*provaElenchi(head,el,all,nem,nr,nc);
        for(t=head;t!=NULL;t=listDelHead(t));*/
        free(nuovo.elenco);
        i++;
    }
    return ;
}
void comb_rip(int pos,int start,int k,Risorsa val,Risorsa sol,int *count,int budget,int spesacorr,Target all,Target nem,int nr,int nc,int *finito){
    int i;
    if(pos>=k){
        //aggiungi elenco alla lista di elenchi da provare
        sol.n = k;
        //headSol = insertHead(headSol, sol);
        if(provaElenco(sol,all,nem,nr,nc)==1){
            *finito=1;
        }
        return;
    }
    for(i=start;i<val.n && *finito==0;i++){
        if(val.elenco[i].occ>0 && (spesacorr+val.elenco[i].c)<=budget) {
            val.elenco[i].occ--;
            sol.elenco[pos] = val.elenco[i];
            *count = *count + 1;
            spesacorr += val.elenco[i].c;
            comb_rip(pos + 1, start, k, val, sol, count, budget, spesacorr,all,nem,nr,nc,finito);
            val.elenco[i].occ++;
            spesacorr=spesacorr-val.elenco[i].c;
            start++;
        }
    }
    return ;
};
void disp_semplici(int *posizioni,Risorsa val,int nc,int nr,int *finito,int **MappaAll,int **MappaNem,int insert){

    int i,j;
    if(insert>=val.n){
        if(controllaSol(posizioni,MappaAll,MappaNem,nr,nc,val)==1){
            *finito=1;
            stampaSol(val,posizioni,nr);
            return;
        }
        return;
    }

    for(i=0;i<nr && *finito==0;i++){
        for(j=0;j<nc && *finito==0;j++) {
            if (posizioni[i] == -1 && MappaAll[i][j] == 0 && MappaNem[i][j] == 0) {
                insert++;
                posizioni[i] = j;
                disp_semplici(posizioni, val, nc, nr, finito, MappaAll, MappaNem, insert);
                insert--;
                posizioni[i] = -1;
            }
        }
    }
}
int controllaSol(int *posizioni,int **MappaAll,int **MappaNem,int nr,int nc,Risorsa val){

    int i,j,l,raggio,k,posc,posr,initc,initr;
    int MappaAllTemp[nr][nc],MappaNemTemp[nr][nc];

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            MappaAllTemp[i][j]=MappaAll[i][j];
            MappaNemTemp[i][j]=MappaNem[i][j];
        }
    }
    l=0;
    for(k=0;k<nr && l<val.n;k++){
        if(posizioni[k]!=-1) {
            raggio = val.elenco[l].r;
            posc = posizioni[k];
            posr = k;
            if (posc - raggio < 0) {
                initc = 0;
            } else {
                initc = posc - raggio;
            }
            if (posr - raggio < 0) {
                initr = 0;
            } else {
                initr = posr - raggio;
            }
            for (i = initr; i <= posr + raggio && i < nr; i++) {
                for (j = initc; j <= posc + raggio && j < nc; j++) {
                    MappaAllTemp[i][j] += val.elenco[l].d;
                    MappaNemTemp[i][j] += val.elenco[l].a;
                }
            }
            l++;
        }

    }

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(MappaAllTemp[i][j]<0){
                return 0;
            }
        }
    }
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(MappaNemTemp[i][j]<0){
                return 0;
            }
        }
    }
    //stampa di debug
    printf("Alleati:\n");
 for(i=0;i<nr;i++){
     for(j=0;j<nc;j++){
         printf("%d",MappaAllTemp[i][j]);
     }
     printf("\n");
 }
 printf("Nemici:\n");
 for(i=0;i<nr;i++){
     for(j=0;j<nc;j++){
         printf("%d",MappaNemTemp[i][j]);
     }
     printf("\n");
 }

    return 1;
}

void stampaSol(Risorsa val, int *posizioni,int nr){
    int i,j=0,costo=0,*posr=malloc(val.n*sizeof(int)),*posc=malloc(val.n*sizeof(int));
    printf("Risorse acquistate:%d\n",val.n);
    for(i=0;i<nr && j<val.n;i++){
        if(posizioni[i]!=-1){
            posr[j]=i;
            posc[j]=posizioni[i];
            j++;
        }
    }
    for(i=0;i<val.n;i++){
        printf("-->Risorsa %d in <%d,%d>:\n\t-raggio d'azione:%d\n"
                       "\t-parametro attacco: %d\n"
                       "\t-parametro difesa: %d\n"
                       "\t-costo: %d\n",val.elenco[i].id,posr[i],posc[i],val.elenco[i].r,val.elenco[i].a,val.elenco[i].d,val.elenco[i].c);
        costo+=val.elenco[i].c;
    }
    printf("Costo totale: %d\n",costo);

}

int provaElenco(Risorsa sol,Target all,Target nem,int nr,int nc){
    int finito=0,i,j;
    int *posizioni=malloc(nr*sizeof(int));
    for(i=0;i<nr;i++){
        posizioni[i]=-1;
    }
    int **MappaAlleati,**MappaNemici;
    MappaAlleati=inizializzaMappa(nr,nc,all);
    MappaNemici=inizializzaMappa(nr,nc,nem);
     //scorro elenco
    //funzione che prova l'ultimo elenco trovato al passo precedente e,se successo,stampa la soluzione e blocca le altre ricorsioni
    disp_semplici(posizioni,sol,nc,nr,&finito,MappaAlleati,MappaNemici,0);
    return finito;
}