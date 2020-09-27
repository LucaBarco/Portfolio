#include <stdio.h>
#include "ST.h"
#include "BST.h"
#define MAX 10



ST leggiFileStazioni(char *nome);
int leggiTessera(char *cardid,char *stationid,int time,ST elencoStazioni,BST elencoUtenti);
int main(int argc,char **argv) {
    if(argc<2){
        printf("Errore nell'inserimento dei parametri!\n");
        return -1;
    }
    int scelta=0,time,res;
    char stationId[MAX],cardid[MAX];
    BST elencoUtenti=Bstinit();
    ST elencoStazioni;
    elencoStazioni=leggiFileStazioni(argv[1]);
    STprint(elencoStazioni);
    while(scelta==0){
        printf("Inserire:\n\tCardId: ");
        scanf("%s",cardid);
        printf("\tstationId: ");
        scanf("%s",stationId);
        printf("\ttempo: ");
        scanf("%d",&time);
        res=leggiTessera(cardid,stationId,time,elencoStazioni,elencoUtenti);
        if(res>0){
            printf("---------------> Noleggio terminato per l'utente %s <---------------\n",cardid);
            printf("---------------> Durata: %d minuti\n",res);
        }
        else{
            if(res==0) {
                printf("---------------> Noleggio iniziato per l'utente %s <---------------\n", cardid);
            }
            if(res==-1){
                printf("--------------> Impossibile avviare/completare il noleggio per assenza di bici/parcheggi!\n");
            }
        }
        printf("Inserire nuovi dati?\n\t0) Si\n\t1) No\n");
        scanf("%d",&scelta);
    }
    return 0;
}
ST leggiFileStazioni(char *nome){
    int i,bici,posti;
    char id[MAX];
    ST st;
    FILE *fp=fopen(nome,"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file!\n");
        return NULL;
    }

    fscanf(fp,"%d",&i);
    st=STinit(i);

    while(fscanf(fp,"%s %d %d",id,&bici,&posti)!=EOF){
        STinsert(st,readStation(id,bici,posti));
    }

    fclose(fp);

    return st;
}
int leggiTessera(char *cardid,char *stationid,int time,ST elencoStazioni,BST elencoUtenti){
    int i=STretrieveIndex(elencoStazioni,stationid);
    Item temp=NewItem(cardid,getSize(elencoStazioni));
    Item user=BSTsearch(elencoUtenti,temp);
    if(ItemEq(user,ItemSetVoid())==1) {
        BSTinsert_leaf(elencoUtenti, temp);
        user=BSTsearch(elencoUtenti,temp);
    }
    printf("Posti:%d\n",STretrievePosti(elencoStazioni,i));
    printf("Bici:%d\n",STretrieveBici(elencoStazioni,i));
        if(ItemTipoOperazione(user)==1 && STretrievePosti(elencoStazioni,i)>0) {
            //devo parcheggiare e ci sono parcheggi
            decreasePosti(elencoStazioni,i);
            increaseBici(elencoStazioni,i);
            return ItemSearchStation(user, STretrieveIndex(elencoStazioni, stationid), time);
        }
        else if (ItemTipoOperazione(user)==0 && STretrieveBici(elencoStazioni,i)>0){
            //devo partire e ci sono biciclette
            decreaseBici(elencoStazioni,i);
            increasePosti(elencoStazioni,i);
            return ItemSearchStation(user, STretrieveIndex(elencoStazioni, stationid), time);
        }
        return -1;
    }