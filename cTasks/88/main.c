#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct{

	char file[8];
	uint32_t off;
	uint32_t len;

}__attribute__ ((packed))data;

int main(int argc,char** argv){

	if(argc!=2) errx(1,"arg");

	int fd=open(argv[1],O_RDONLY);
	if(fd<0) err(2,"error opening file");

	data d;
	struct stat st;
	if(stat(argv[1],&st)<0) err(3,"Error stat file");
	if(st.st_size%sizeof(uint8_t)!=0) errx(4,"invalid format");
	if(st.st_size/sizeof(d)>8) errx(5,"too many elements");

	int p[2];
	if(pipe(p)<0) err(4,"error pipe");

	int bytes;
	uint16_t x=0x0000;
	if((bytes=read(fd,&d,sizeof(d)))>0){

		if(d.file[7]!=0x00) errx(9,"Invalid name");

		int f=open(d.file,O_WRONLY);
		if(f<0) err(7,"error opening file");

		if(st.st_size>(d.off+d.len)*sizeof(uint16_t)) errx(10,"invalid data");

		close(p[0]);

		lseek(f,d.off*sizeof(uint16_t),SEEK_SET);
		uint16_t r;
		for(int i=0;i<d.len;i++){
			read(f,&r,sizeof(r));
			r^=x;
		}
		write(p[1],&r,sizeof(r));
		close(f);
	}

	if(bytes<0) err(6,"error reading file");

	close(p[1]);
	uint16_t e;
	while(read(p[0],&e,sizeof(e))>0){

		e^=x;
	}
	dprintf("result: %d",e);
exit(0);

}
