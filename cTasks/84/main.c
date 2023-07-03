#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc,char** argv){

	
	int p[2];
	pipe(p);
	
pid_t pid=fork();
	if(pid<0){
		err(1,"Error: cannot fork");
	}

	if(pid==0){
		close(p[0]);
		dup2(p[1],1);
		execlp("find","find",argv[1],"-type","f","-printf","%T@ %p\n",(char*)NULL);
	}

	close(p[1]);
	
int b[2];
	pipe(b);

	pid_t newPid=fork();
	if(newPid==0){
		dup2(p[0],0);
		close(b[0]);
	dup2(b[1],1);	
		execlp("sort","sort","-r","-n",(char*)NULL);
	}
close(b[1]);

int c[2];
pipe(c);
pid_t oPid=fork();
if(oPid==0){
	close(c[0]);
	 dup2(b[0],0);
	 dup2(c[1],1);
	 execlp("head","head","-n","1",(char*)NULL);
}

close(c[1]);
dup2(c[0],0);
execlp("cut","cut","-d"," ","-f","2",(char*)NULL);

}
