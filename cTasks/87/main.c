#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc,char** argv){

	if(argc!=3) errx(1,"arg");

	int fd1=open(argv[1],O_RDONLY);
	if(fd1<0) err(2,"error opening file");

	int p[2];
	if(pipe(p)<0) err(3,"error");

	pid_t pid=fork();
	if(pid<0) err(4,"erroro fork");

	if(pid==0){
		close(p[0]);
		dup2(p[1],1);

		if(execlp("cat","cat",argv[1],(char*)NULL)<0)
			err(5,"error exec");
	}

	close(p[1]);

	int fd2=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);
	if(fd2<0) err(6,"error open");

	uint8_t c=0;
	uint8_t t=0;
	ssize_t rs=0;
	uint8_t x=0x20;

	while((rs=read(p[0],&c,sizeof(c)))==sizeof(c)){
		switch(c){
			case 0x55: 
				continue;
			case 0x7D:
				if(read(p[0],&t,sizeof(t))!=sizeof(t)){
					err(7,"error read");
				}
				if((t!=0x20) && (t!=0xDF) && (t!=0x75) && (t!= 0x5D)){
					err(8,"Invalid byte");
				}
				c=t^x;
				dprintf("%x\n",c);

				__attribute__ ((fallthrough));
			default:
				if(write(fd2,&c,sizeof(c)) != sizeof(c)){
						err(9,"error write");
						}
						}
						}
						close(fd1);
						close(fd2);
						close(p[0]);
						return 0;
}
