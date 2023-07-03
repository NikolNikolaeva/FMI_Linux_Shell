#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(int argc, char** argv){

	if(argc!=4){
		errx(1,"Tree arg expected");
	}

	for(int i=1;i<argc;i++){
	
		pid_t pid=fork();

		if(pid<0){
			err(2,"erorr with fork");
		}

		int status;
		if(pid>0){
		
			wait(&status);
			if(WIFEXITED(status) && WEXITSTATUS(status)==0){
				dprintf(1,"pid: %d, exit status:%d\n",pid,WEXITSTATUS(status));
			}
		}
		else{
		
			if((execlp(argv[i],argv[i],(char*)NULL))<0){
				err(3,"eror with exec");
			}
		}
	}

	return 0;
}

