#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char*argv[]){
    int n,i;
    int *v;
    pid_t pid;
    if(argc<2){
    printf("Parameters error!\n");
    return -1;
    }
    n=atoi(argv[1]);

    v=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        pid=fork();
        if(pid!=0){
            v[i]=0;
        }
        else{
            v[i]=1;
        }
    }
    for(i=0;i<n;i++){
        //print -> I probably need a semphore because it's possible that more threads print at the same time
        printf("%d",v[i]);
    }
    printf("\n");
    free(v);
    return 0;

}