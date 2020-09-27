#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 10
void waitRandomTime(int max){
    sleep((int) (rand() % max)+1);
}

struct st_p{
    pthread_t tid;
    sem_t empty,*full;
    int *buffer,tail;
};

struct st_c{
    pthread_t tid;
    sem_t full,*empty;
    int *buffer,head;
};
void *P(void *par);
void *C(void *);
int main(){
    srand(getpid());
    int buffer[SIZE];
    struct st_p producer;
    struct st_c consumer;

    consumer.buffer=buffer;
    producer.buffer=buffer;
    producer.tail=0;
    consumer.head=0;
    sem_init(&consumer.full,0,0);
    producer.full=&consumer.full;
    sem_init(&producer.empty,0,SIZE);
    consumer.empty=&producer.empty;

    pthread_create(&producer.tid,NULL,P,(void *)&producer);
    pthread_create(&consumer.tid,NULL,C,(void *)&consumer);

    pthread_join(producer.tid,NULL);
    pthread_join(consumer.tid,NULL);

    sem_destroy(&consumer.full);
    sem_destroy(&producer.empty);
    

return 0;
}

void *P(void *par){
    struct st_p *producer=(struct st_p *)par;
    int nP=0;
    
    while(nP!=-1){
        // waitRandomTime(10);
        if(nP==1000){
            nP=-1;
        }
        sem_wait(&(producer->empty));
       // sem_wait(&(producer->meP));
        producer->buffer[producer->tail]=nP;
        producer->tail=((producer->tail)+1)%SIZE;
       // sem_post(&(producer->meP));
        sem_post((producer->full));
        if(nP!=-1){
        nP++;
        printf("Produced:%d\n",nP);
        }
    }
    pthread_exit((void *)0);
}

void *C(void *par){
 struct st_c *consumer=(struct st_c *)par;
 FILE *fp=fopen("out.txt","w");
int nC;
    while(1){
      //  waitRandomTime(10);
        sem_wait(&(consumer->full));
       // sem_wait(&(consumer->meC));
        nC=consumer->buffer[consumer->head];
        if(nC!=-1){
            printf("Consumed:%d\n",nC);
            fprintf(fp,"%d\n",nC);
        }
        else{
            fclose(fp);
            pthread_exit((void *) 0);
        }
        consumer->head=((consumer->head)+1)%SIZE;
       // sem_post(&(consumer->meC));
        sem_post((consumer->empty));
    }

}