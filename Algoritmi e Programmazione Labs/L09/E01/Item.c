//
// Created by Luca Barco on 19/12/2017.
//

#include "Item.h"
#include <string.h>

//funzione estrazione chiave
char *KEYget(Item i){
    return i.key;
}


//ItemScan
Item ITEMscan(FILE *fp,int *dx,int *sx){
    Item x;
    char chiave[20];
    int t1,t2;
    if(fscanf(fp,"%s %d %d %d\n",chiave,&x.N,&t1,&t2)!=EOF){
        x.key=strdup(chiave);
        *sx=t1;
        *dx=t2;
        return x;
    }
    else{
        return ITEMsetVoid();
    }
}
//ITEMprint
void ITEMprint(FILE *fp,Item x){
    fprintf(fp,"%s %d\n",x.key,x.N);
}

//ITEMequal
int ITEMequal(Item a,Item b){
    if(strcmp(a.key,b.key)==0){
        return 0;
    }
    return -1;
}

//funzione ItemSetVoid
Item ITEMsetVoid(){
    Item x;
    x.key=strdup("\0");
    x.N=0;
    return x;
}