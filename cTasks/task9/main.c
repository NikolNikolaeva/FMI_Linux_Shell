#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,char** argv){

	int fd= open(argv[1],O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
if(fd<0){
	err(1,"error");
}

	pid_t pid=fork();

	if(pid==0){
	
		write(fd,"foo",3);
	}
	else{

		wait(NULL);
		write(fd,"bar",3);
	}
}
