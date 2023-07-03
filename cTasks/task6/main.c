
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc,char** argv){

	if(argc!=2){
		errx(1,"One arg expected: ./main <command>");
	}

	pid_t pid=fork();

	if(pid<0){
		err(2,"erorr with fork");
	}

		int status;
		
	if(pid>0){

		wait(&status);
		if(WIFEXITED(status)&&WEXITSTATUS(status)==0){
		printf("%s",argv[1]);
		}
		else{
			errx(3,"erorr with wait");
		}
	}
	else{
		if((execlp(argv[1],argv[1],(char*)NULL))<0){
		
			err(4,"error with exec");
		}
	}

	return 0;

}
