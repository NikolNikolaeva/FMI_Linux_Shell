#include <err.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){

//	if(argc>1){errx(1,"no arg needed");}

	int pid=fork();

	if(pid<0){
		err(2,"erorr with fork");
	}
	else if (pid==0){
		if((execlp("cp","cp","/etc/passwd",".",(char*)NULL))<0)
		{
			err(3,"erorr with exec");
		}
	}
	else{
		int status;
		wait(&status);
		if(WIFEXITED(status)&&WEXITSTATUS(status)==0){
		if((execlp("sed","-i","-F","s/:/?/g","./passwd"))<0)
				{
					err(3,"error with exec");
				}
		}
	}
}
