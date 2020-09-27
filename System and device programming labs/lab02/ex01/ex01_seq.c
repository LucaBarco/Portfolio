#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float mul(float *v1,float *v2,float **mat, int n);
void randomFill(float *v1,float *v2, float **mat, int n, float min, float max);
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
    int i,j;
    float s;

    v=(float *)malloc(n*sizeof(float));
    printf("Vector v just created!\n");
    for(i=0;i<n;i++){
        printf("I'm in column %d\n",i);
        v[i]=0;
        for(j=0;j<n;j++){
            printf("\tv1[%d]*mat[%d][%d]=%f*%f=%f\n",j,j,i,v1[j],mat[j][i],v1[j]*mat[j][i]);
            v[i]+=v1[j]*mat[j][i];
        }
        printf("v[%d]=%f\n",i,v[i]);
    }
    printf("first result done - I'm here\n");
    s=0;
    for(i=0;i<n;i++){
        s+=v[i]*v2[i];
       printf("\tv[%d]*v2[%d]=%f*%f=%f\n",i,i,v[i],v2[i],v[i]*v2[i]);
    }
    printf("Result total:%f\n",s);
    return s;
}