#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc,char** argv){

	if(argc!=3) errx(1,"Invalid count of arg");

	int fd1=open(argv[1],O_RDONLY);
	if(fd1<0) err(2,"error opening file");

	int fd2=open(argv[2],O_RDONLY);
	if(fd2<0) err(2,"error opening file");

	struct stat st1;
	if(stat(argv[1],&st1)<0) err(3,"error stat file");

	struct stat st2;
	if(stat(argv[2],&st2)<0) err(3,"error stat file");

	if(st2.st_size%sizeof(uint16_t)!=0) errx(4,"invalid format file");
	if((long unsigned int)st1.st_size*CHAR_BIT!=(st2.st_size/sizeof(uint16_t))) errx(5,"files are not same size");

	int fd3=open("newFile",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU);
	if(fd3<0) err(6,"error opening file");

	uint8_t sclbuf;
	uint16_t sdlbuf;
	uint16_t counter=0;

	while(read(fd1,&sclbuf,sizeof(sclbuf))>0){

		for(int i=7; i>=0;i--){
			if((sclbuf & (1<<i))!=0){
			
				lseek(fd1,counter*sizeof(uint16_t),SEEK_SET);
				read(sdl,&sdlbuf,sizeof(sdlbuf))!=sizeof(sdlbuf);
				write(fd3,&sdlbuf,sizeof(sdlbuf));

			}
			
			counter++;
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}

