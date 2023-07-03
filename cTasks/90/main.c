#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char** argv){

	if(argc!=3) errx(1,"Wrong count of srg. Usage: %s [1-9] [1-9]",argv[0]);

	int N=atoi(argv[1]);
	int D=atoi(argv[2]);

	if(N<=0 || N>9 || D<0 || D>9) errx(2,"Invalid arguments");
	
	int p1[2];
	int p2[2];
	if(pipe(p1)<0 || pipe(p2)<0) err(4,"error making pipe");
	int a=42;
	pid_t pid =fork();
	if(pid<0) err(3,"error forking the process");

	if(pid==0){
		close(p1[0]);
		close(p2[1]);

	for(int i=0; i<N; i++){
		
		read(p2[0],&a,sizeof(a));
		write(1,"DONG\n",5);

		write(p1[1],&a,sizeof(a));
	}

	}else{

		close(p2[0]);
		close(p1[1]);
for(int i=0;i<N;i++){
		write(1,"DING ",6);
		write(p2[1],&a,sizeof(a));
		read(p1[0],&a,sizeof(a));

		sleep(D);
}

	}

	close(p2[1]);
	close(p1[0]);
	exit(0);
}


