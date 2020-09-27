#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <semaphore.h>

struct tp{
    int *v;
    int n,d,id;
    sem_t *me;
    sem_t *barrier1,*barrier2,*mutex;
};
int NTHREADS, count=0;
void *tF(void *pars);
int main(int argc, char *argv[]){
    
    int i;
    sem_t *me, barrier1,barrier2,mutex;
    struct tp* tArgs;
    pthread_t *threadId;
    if(argc<2){
        printf("Parameters error!\n");
        exit(-1);
    }

    int n=atoi(argv[1]);
    int d=pow(2,n);
    int *v=(int *)malloc(d*sizeof(int));

    
    srand(time(0)+sqrt(time(0)));

    printf("The vector is:\n");
    for(i=0;i<d;i++){
    v[i]=rand()%(9)+1;
    printf("\t%d",v[i]);
    }
    printf("\n");

    me=(sem_t *)malloc(d*sizeof (sem_t));
    for(i=0;i<d;i++){
        sem_init(&me[i],0,1);
    }
    sem_init(&barrier1,0,0);
    sem_init(&barrier2,0,0);
    sem_init(&mutex,0,1);
    NTHREADS=d-1;
    tArgs=(struct  tp*)malloc((d-1)*sizeof(struct tp));
    threadId=(pthread_t *)malloc((d-1)*sizeof(pthread_t));
    for(i=0;i<d-1;i++){
        tArgs[i].v=v;
        tArgs[i].d=d;
        tArgs[i].n=n;
        tArgs[i].id=i+1;
        tArgs[i].me=me;
        tArgs[i].barrier1=&barrier1;
        tArgs[i].barrier2=&barrier2;
        tArgs[i].mutex=&mutex;
        pthread_create(&threadId[0],NULL,tF,(void *)&tArgs[i]);
    }
    printf("\nThe result vector is:\n\t%d",v[0]);
    for(i=0;i<d-1;i++){
        pthread_join(threadId[i],NULL);
        printf("\t%d",v[i+1]);
    }
    printf("\n");
    
    sem_destroy(&mutex);
    for(i=0;i<d;i++){
    sem_destroy(&me[i]);
    }
    sem_destroy(&barrier1);
    sem_destroy(&barrier2);
    free(threadId);
    free(tArgs);
    free(v);
    return 0;
}
void *tF(void *pars){
    struct tp *args=(struct tp *)pars;
    sem_t *barrier1,*barrier2,*me, *mutex;
    int i,d,n,gap=1,k,*v,j;
    v=args->v;
    barrier1=args->barrier1;
    barrier2=args->barrier2;
    me=args->me;
    mutex=args->mutex;
    d=args->d;
    n=args->n;
    i=args->id;
    int tempres;
    for(k=0;k<n;k++){
                      //  printf("Thread %d:\n\t\tI'm waiting for v[%d]=%d and v[%d]=%d\n",i,i,v[i],i-gap,v[i-gap]);
        sem_wait(&me[i-gap]);
        sem_wait(&me[i]);
        tempres=v[i]+v[i-gap];
                       // printf("\n\t\tv[%d]=%d\n",i,v[i]);
        sem_post(&me[i]);
        sem_post(&me[i-gap]);
        sem_wait(mutex);
        count++;
                  //      printf("Thread %d\n\t\t\tcount of terminated threads:%d\n",i,count);
        if(count==NTHREADS){
            //last thread
                //        printf("Hey, I'm the last thread (%d)! I've just woke up all the others! ;-)\n",i);
            for(j=0;j<NTHREADS;j++){
              //          printf("Thread %d:\t\t\t\t\tpost number %d\n",i,j);
                sem_post(barrier1);
            }
        }
    sem_post(mutex);
            //printf("Thread %d: \t\t\t\t\tI have just posted the mutex!\n",i);
            //printf("Thread %d:\t\t\t\t\tI'm just waiting for the barrier1!\n",i);
    sem_wait(barrier1);
            //printf("Thread %d:\t\t\t\t\tI'm just waiting for the mutex!\n",i);
    v[i]=tempres;
    sem_wait(mutex);
    count--;
            //printf("\t\t\t\t\t\tcount:%d!\n",count);
    if(count==0){
        //last thread
       /* printf("Current vector:\n");
        for(int z=0;z<d;z++){
            printf("\t%d",v[z]);
        }
        printf("\n");*/
        int temp=NTHREADS;
        if(NTHREADS==d-1){
            NTHREADS=NTHREADS-1;
        }
        else{
            NTHREADS=NTHREADS-2;
        }
              //  printf("-------------- Current running %d threads ------------\n",NTHREADS);
        for(j=0;j<temp;j++){
            sem_post(barrier2);
        }
    }

    sem_post(mutex);
            //printf("Thread %d:\t\t\t\t\tI have just posted the mutex!\n",i);
            //printf("Thread %d:\t\t\t\t\tI'm just waiting for the barrier2!\n",i);
    sem_wait(barrier2);
    gap=2*(k+1);
            // printf("\t\t\t\t\tMy new gap is %d\n",gap);
    if(i-gap<0){
        pthread_exit((void*)0);
    }
    }
    pthread_exit((void*)0);
}