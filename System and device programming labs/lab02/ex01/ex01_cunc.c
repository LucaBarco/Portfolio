#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
int count=0;
int NTHREADS;

struct par{
    float *v1;
    float **mat;
    float *v;
    float *v2;
    int id;
    int n;
    pthread_mutex_t *mutex;
};


float mul(float *v1,float *v2,float **mat, int n);
void randomFill(float *v1,float *v2, float **mat, int n, float min, float max);
void *tP(void *tArgs);



int main(int argc, char *argv[]){
int n,i;
float sum;
/*
float v1[5]={-0.0613,-0.1184,0.2655,0.2952,-0.3131};
float v2[5]={-0.3235,0.1948,-0.1829,0.4502,-0.4656};
float mat[5][5]={
    {-0.3424, -0.3581,  0.1557,  0.2577,  0.2060},
    { 0.4706, -0.0782, -0.4643,  0.2431, -0.4682},
    { 0.4572,  0.4157,  0.3491,  0.1078, -0.2231},
    { -0.0146,  0.2922,  0.4340, -0.1555, -0.4029},
    {0.3003,  0.4595,  0.1787, -0.3288, -0.4656 }
};
n=5;*/
float  *v1,*v2,**mat;

if(argc<2){
    printf("Parameters error!\n");
    exit(1);
}
n=atoi(argv[1]);

//init
v1=(float *)malloc(n*sizeof(float));
v2=(float *)malloc(n*sizeof(float));

mat=(float **)malloc(n*sizeof(float *));
for(i=0;i<n;i++){
    mat[i]=(float *)malloc(n*sizeof(float));
}

randomFill(v1,v2,mat,n,-0.5,0.5);
sum=mul(v1,v2,mat,n);
printf("result: %f\n",sum);


    return 0;
}

void randomFill(float *v1,float *v2, float **mat, int n, float min, float max){
    int i,j;
    int rmin=-100248,rmax=100128;
    srand(time(0));
    for(i=0;i<n;i++){
        v1[i]=((((float)(rand()%(rmax-rmin+1))+rmin)-rmin)/(rmax-rmin))*(max-min)+min;
        v2[i]=((((float)(rand()%(rmax-rmin+1))+rmin)-rmin)/(rmax-rmin))*(max-min)+min;
        for(j=0;j<n;j++){
            mat[i][j]=((((float)(rand()%(rmax-rmin+1))+rmin)-rmin)/(rmax-rmin))*(max-min)+min;
        }
    }
    printf("v1 = [\n");
    for(i=0;i<n;i++){
        printf("\t%f",v1[i]);
    }
    printf("]\n");

    printf("v2 = [\n");
    for(i=0;i<n;i++){
        printf("\t%f",v2[i]);
    }
    printf("]\n");

    printf("mat = [\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
        printf("\t%f",mat[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

float mul(float *v1,float *v2,float **mat, int n){
    float *v;
    int i;
    float s;

    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    struct par *parTh;
    parTh=(struct par *)malloc(n*sizeof(struct par));
    pthread_t *tid=(pthread_t*)malloc(n*sizeof(pthread_t));

    v=(float *)malloc(n*sizeof(float));
    printf("Vector v just created!\n");

//this thread must create n threads -> each one should compute che i-th element of v vector (v1*mat[][i])
NTHREADS=n;
    for(i=0;i<n;i++){
        parTh[i].id=i;
        parTh[i].mutex=&mutex;
        parTh[i].v=v;
        parTh[i].v1=v1;
        parTh[i].v2=v2;
        parTh[i].mat=mat;
        parTh[i].n=n;
        pthread_create(&tid[i],NULL,tP,(void *)&parTh[i]);
    }
    for(i=0;i<n;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    free(parTh);
    free(tid);


    printf("first result done:\nV:\n\n");
    for(i=0;i<n;i++){
        printf("\t%f",v[i]);
    }
    printf("\n");
    s=0;
    for(i=0;i<n;i++){
        s+=v[i]*v2[i];
       printf("\tv[%d]*v2[%d]=%f*%f=%f\n",i,i,v[i],v2[i],v[i]*v2[i]);
    }
    printf("Result total (Main Thread):%f\n",s);
    return s;
}
void *tP(void *tArgs){
    
    struct par *args=(struct par *)tArgs;
    int i=0,n=args->n;
    float sum=0;
    for(i=0;i<n;i++){
        sum+=(args->v1)[i]*(args->mat)[i][args->id];
    }
    pthread_mutex_lock(args->mutex);
    (args->v)[args->id]=sum;
    count++;
    if(count==NTHREADS){
        printf("Hi I'm the last thread!\n");
        float s=0;
    for(i=0;i<n;i++){
        s+=(args->v)[i]*(args->v2)[i];
       printf("\tv[%d]*v2[%d]=%f*%f=%f\n",i,i,(args->v)[i],(args->v2)[i],(args->v)[i]*(args->v2)[i]);
    }
     printf("Result total (Last Thread):%f\n",s);
    }
    pthread_mutex_unlock(args->mutex);
    pthread_exit((void *)0);  
}