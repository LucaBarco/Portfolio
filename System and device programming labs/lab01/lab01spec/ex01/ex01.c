#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[]){

FILE *fpi,*fpo2;
int fi,fo1;
char str[100], path[3]={'.','/','\0'}, buf[4096];
int id,mark;
char name[31],surname[31];
long int reg;
int i=0,rbytes,nbytes=2*sizeof(int)+sizeof(long int)+62*sizeof(char);


if(argc<4){
printf("Missing parmeters!\n");
return -1;
}

fi=open(argv[1], O_RDONLY);

fo1=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

if(fi==-1||fo1==-1){
printf("Cannot open binary files!\n");
return -1;
}
while((rbytes=read(fi,buf, nbytes))!=0){
	write(fo1,buf,rbytes);
}
close(fi);
close(fo1);


fpi=fopen(argv[1],"r");
fpo2=fopen(argv[3],"w");

if(fpi==NULL||fpo2==NULL){
printf("Cannot open files!");
return -1;
}

while(fscanf(fpi,"%d %ld %s %s %d",&id,&reg,surname,name,&mark)!=EOF){
if(i==0){i++;}else{fprintf(fpo2,"\n");}
fprintf(fpo2,"%d %ld %s %s %d",id,reg,surname,name,mark);
}
fclose(fpi);
fclose(fpo2);


return 0;
}