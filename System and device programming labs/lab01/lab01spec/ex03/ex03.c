#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int main(){

int fp;
int pipe_id[2];
pid_t pid;
char str[100],buf[4096];
int rbytes,totbytes=0,nbytes=100*sizeof(char),modbytes=0;
if(pipe(pipe_id)==-1){
printf("Cannot create pipe!\n");
}
fp=open("file.txt",O_RDWR);
if(fp==-1){printf("Cannot open file!\n");}

pid=fork();
if(pid!=0){
//father
	close(pipe_id[0]);
	totbytes=0;
	
	while((rbytes=read(fp,buf,nbytes))!=0){
	totbytes+=rbytes;
	write(STDOUT_FILENO, buf, rbytes);
	}
	
	fscanf(stdin,"%s",str);
	while(strcmp(str,"end")!=0){
	if(strcmp(str,"END")==0){close(fp);kill(pid,SIGKILL);exit(1);}
	strcat(str,"\n");
	totbytes+=write(fp,str,strlen(str)*sizeof(char));
	fscanf(stdin,"%s",str);	
	}
	fprintf(stdout,"I'm at the end of father process with fp:%d\n",fp);
	write(pipe_id[1],&totbytes,sizeof(int));
	wait(NULL);
	
}
else{
//child
	
	close(pipe_id[1]);
	
	
	read(pipe_id[0],&modbytes,sizeof(int));
	fprintf(stdout,"I'm in the child process with fp:%d\n",fp);
	lseek(fp,(off_t)0,SEEK_SET);
	while((rbytes=read(fp,buf,nbytes))!=0){
	write(STDOUT_FILENO, buf, rbytes);
	}
	fscanf(stdin,"%s",str);	
	while(strcmp(str,"end")!=0){
	if(strcmp(str,"END")==0){close(fp);exit(1);}
	strcat(str,"\n");
	write(fp,str,strlen(str)*sizeof(char));	
fscanf(stdin,"%s",str);	
	}
	
}




return 0;
}