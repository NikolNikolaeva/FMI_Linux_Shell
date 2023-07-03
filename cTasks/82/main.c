#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

int main(int argc,char** argv){

	int p[2];
	pipe(p);

	pid_t pid=fork();
	if(pid<0) err(1,"error forking");

	if(pid==0){

		close(p[0]);
		dup2(p[1],1);
		execlp("cut","cut","-d",":","-f","7","/etc/passwd",(char*)NULL);
		err(2,"error executing command cut");
	}

	close(p[1]);
	int p2[2];
	pipe(p2);

	pid_t pid2=fork();

	if(pid2==0){
	
		dup2(p[0],0);
		close(p2[0]);
		dup2(p2[1],1);

		execlp("sort","sort",(char*)NULL);
		err(2,"error executing sort");
	}

	close(p2[1]);

	int p3[2];
	pipe(p3);

	pid_t pid3=fork();

	if(pid3==0){
		dup2(p2[0],0);
		close(p3[0]);
		dup2(p3[1],1);
		execlp("uniq","uniq","-c",(char*)NULL);
		err(2,"érroro executing uniq -c");
	}

	close(p3[1]);
	dup2(p3[0],0);
	execlp("sort","sort","-n",(char*)NULL);
	err(2,"error executing sort");

	exit(0);
}
