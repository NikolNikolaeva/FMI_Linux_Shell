#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char** argv){

	if(argc!=2) errx(1,"Wrong count of arg");

	int p[2];
	if(pipe(p)<0) err(2,"error pipr");

	pid_t pid=fork();
	if(pid<0) err(3,"error fork");

	if(pid==0){
		close(p[0]);
		dup2(p[1],1);

		execlp("cat","cat",argv[1],(char*)NULL);
		err(4,"error exec");
	}else{

		close(p[1]);
		dup2(p[0],0);
		execlp("sort","sort",(char*)NULL);

	}

	//close(p);
	wait(NULL);
	exit(0);
}
