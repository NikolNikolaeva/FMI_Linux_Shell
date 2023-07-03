#include <stdio.h>
#include <err.h>
#include <unistd.h>

int main(int argc,char** argv)
{
	if(argc<2){errx(1,"error arr needed");}

	for(int i=1;i<argc;i++){
		int pid_pr=fork();
		if(pid_pr==0){
	if((execlp("cp","cp",argv[i],".",(char*)NULL))<0)
	{
		err(3,"error with exec");
	}
			}
	

	if(pid_pr<0){err(2,"error with fork");}
	}
	return 0;
}
