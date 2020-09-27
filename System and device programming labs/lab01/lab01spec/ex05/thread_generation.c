#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct st{
    pthread_t *tree;
    int n;
    int id;
    int l;
};
void *threadFunction(void * par);

int main(int argc, char *argv[]){

    int l,m=1,i;
    struct st *v_thread;
    if(argc<2){
        printf("Parameters error!\n");
        return -1;
    }
    
    l=atoi(argv[1]);
   /*  for(i=0;i<l;i++){
        m=m*2;
    } */
    v_thread= (struct st*) malloc(2*sizeof(struct st));
    for(i=0;i<2;i++){
        v_thread[i].n=l;
        v_thread[i].id=i;
        v_thread[i].l=l;
        v_thread[i].tree=(pthread_t *) malloc((l+1)*sizeof(pthread_t));
    }

   for(int i=0;i<2;i++){
       v_thread[i].tree[0]=pthread_self();
       pthread_create(&v_thread[i].tree[1],NULL,threadFunction,(void *) &v_thread[i]);
       //printf("Level %d: create thread %d %ld\n",l,i,v_thread[i].tree[1]);
   }
    for(i=0;i<2;i++){
        pthread_join(v_thread[i].tree[1],NULL);
    }
    for(i=0;i<2;i++){
        free(v_thread[i].tree);
    }
    free(v_thread);
    
    return 0;
}

void *threadFunction(void * par){
    struct st *arg=(struct st *) par;
    struct st *v_thread;
    int i,j, l=arg->l;
    int n=arg->n;
    n--;
   // printf("%d\n",n);
    if(n>0){
        //create 2 threads
     
        v_thread= (struct st*) malloc(2*sizeof(struct st));
        for(i=0;i<2;i++){
        v_thread[i].n=n;
        v_thread[i].id=(arg->id)+1;;
        v_thread[i].l=l;
        v_thread[i].tree=(pthread_t *) malloc((l+1)*sizeof(pthread_t));
        for(j=0;j<=l;j++){
            v_thread[i].tree[j]=arg->tree[j];
        }
    }
           
      for(i=0;i<2;i++){
       pthread_create( &v_thread[i].tree[l-n+1],NULL,threadFunction,(void *) &v_thread[i]);
      // printf("Level %d: create thread %d %ld\n",n,i,v_thread[i].tree[l-n+1]);
   }
      for(i=0;i<2;i++){
        pthread_join(v_thread[i].tree[l-n+1],NULL);
    }  
    for(i=0;i<2;i++){
        free(v_thread[i].tree);
    }
    free(v_thread);
    }
    else{
        //print my three and exit -> probably I need a semphore because it's possible that more threads print at the same time
        for(i=0;i<l;i++){
            printf("%ld\t",arg->tree[i]);
        }
        printf("\n");
        pthread_exit((void *)0);
    }
}