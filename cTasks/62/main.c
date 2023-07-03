#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct{

	uint16_t off;
	uint8_t b;
	uint8_t nb;
}__attribute__((packed))data;

int main(int argc,char** argv){

	if(argc!=4){
		errx(1,"count of arg");
	}

	int fd1=open(argv[1],O_RDWR);
	if(fd1<0){
		err(2,"error  opening file");
	}

	int fd2=open(argv[2],O_RDWR);
	if(fd1<0){
		err(2,"error  opening file");
	}

	int fd3=open(argv[3],O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);
	if(fd1<0){
		err(2,"error  opening file");
	}

	struct stat st1;
	struct stat st2;

	if(stat(argv[1],&st1)<0){
		err(3,"error stat file");
	}
	if(st1.st_size % sizeof(uint8_t)!=0){
		errx(4,"Invalid format");
	}


	if(stat(argv[2],&st2)<0){
		err(3,"error stat file");
	}
	if(st2.st_size % sizeof(uint8_t)!=0){
		errx(4,"Invalid format");
	}

	if(st1.st_size!=st2.st_size){
		errx(5,"not same length");
	}
	
	data d;

	uint8_t f1;
	uint8_t f2;
	int bytes_read;
	d.off=0;

	while((bytes_read=read(fd1,&f1,sizeof(f1)))>0){
	
		if(read(fd2,&f2,sizeof(f2))<=0){
			err(6,"error reading");
		}

		d.off+=1;
		if(f1==f2){
			continue;
		}
		d.b=f1;
		d.nb=f2;

		if(write(fd3,&d,sizeof(d))!=sizeof(d)){
			err(7,"error writing");
		}

	}

	if(bytes_read<0){
		err(6,"error reading");

		close(fd1);
		close(fd2);
		close(fd3);
		exit(0);
	}
}
