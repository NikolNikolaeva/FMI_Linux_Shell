#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

typedef struct{

	uint16_t off;
	uint8_t b;
	uint8_t nb;
}__attribute__((packed))data;

int main(int argc,char** argv){

	if(argc!=4){
		warnx("Usage: %s <patch>.bin <f1>.bin <f2>.bin",argv[0]);
		errx(1,"Three argument expected");
	}
	
	int fd1=open(argv[2],O_RDONLY);
	if(fd1<0) err(2,"Error opening file");

	int fdP=open(argv[1],O_RDONLY);
	if(fdP<0) err(2,"Error opening file");

	int fd2=open(argv[3],O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);
	if(fd2<0) err(2,"Error sreating file");

	struct stat s1;

	if(stat(argv[2],&s1)<0) err(3,"Error stat file");
	if(s1.st_size%sizeof(uint8_t)!=0) errx(4,"Invalid format of file f1");

	struct stat stP;
	data d={.off=0, .b=0, .nb=0};

	if(stat(argv[1],&stP)<0) err(3,"Error stat file");
	if(stP.st_size%sizeof(d)!=0) errx(4,"Invalid format of the file p");

	int size=s1.st_size;

	uint8_t b;
	while(read(fd1,&b,sizeof(b))>0){

		write(fd2,&b,sizeof(b));
	}
	
	while(read(fdP,&d,sizeof(d))>0){
		write(1,&d.b,sizeof(d.b));

		if(lseek(fd1,d.off,SEEK_SET)<0) err(5,"error seeking");

		if(read(fd1,&b,sizeof(b))<0) err(7,"err reading fd1");
		//write(1,&b,sizeof(b));
		//write(1,&d.b,sizeof(d.b));
		if(d.b==b){
			lseek(fd2,d.off,SEEK_SET);
			write(fd2,&d.nb,sizeof(d.nb));
		}
		else errx(8,"not same");
	}

}
