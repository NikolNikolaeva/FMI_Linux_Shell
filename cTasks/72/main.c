#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct{
	uint16_t off,len;
}Interval;

typedef struct{
	Interval post,pre,in,suf; 
}Complect;

Complect c;

typedef struct{
	uint32_t f;
	uint16_t count;
	uint32_t fill;
	uint32_t unused;
}header;

int openToRead(char* file,int size,header* h);
int openToRead(char* file,int size,header* h){

	int fd=open(file,O_RDONLY);
	if(fd<0){
		err(2,"error openig file");
	}

	struct stat s;
	if(stat(file,&s)<0){
		err(3,"error stat file");
	}

	if((s.st_size-sizeof(h))%size!=0){
		errx(4,"invalid file size");
	}
	return fd;
}

char* myRead(int fd,const char* file,int elSize,Interval* interval, int*readBytes);
char* myRead(int fd,const char* file,int elSize,Interval* interval, int*readBytes){

	int blockSize=interval->len*elSize;
	char* arr=(char*)malloc(blockSize);

	if(lseek(fd,interval->off*elSize,SEEK_SET)<0){
		err(5,"error seeking");
	}
	if((*readBytes=read(fd,arr,blockSize))<0){
		err(6,"error reading");
	}

	return arr;
}

int myWrite(int fd1,char* arr,int blockSize);
int myWrite(int fd1,char* arr,int blockSize){

	int bytes=0;
	if((bytes=write(fd1,arr,blockSize))!=blockSize){
		err(7,"error writing block to file");
	}

	return bytes;
}

int main(int argc,char** argv){

	if(argc!=7) errx(1,"Wrong num of arg");

	header affh;
	header posth;
	header preh;
	header infh;
	header suffh;

	int fdaffix=openToRead(argv[1],2,&affh);
int fdpostfix=openToRead(argv[2],4,&posth);
int fdprefix=openToRead(argv[3],1,&preh);
int fdinfix=openToRead(argv[4],2,&infh);
int fdsuffix=openToRead(argv[5],8,&suffh);

int fd=open(argv[6],O_CREAT|O_TRUNC|O_RDWR,S_IRWXU);

if(fd<0){
	err(8,"error creating file");
}

int bytes=0;

while((bytes=read(fdaffix,&c,sizeof(c)))>0){

	int readBytes=0;
	char* arr=myRead(fdpostfix,argv[2],4,&c.post,&readBytes);
	int writtenBytes=myWrite(fd,arr,readBytes);
	free(arr);

	arr=myRead(fdprefix,argv[3],1,&c.pre,&readBytes);
	writtenBytes=myWrite(fd,arr,readBytes);
	free(arr);


	arr=myRead(fdinfix,argv[4],2,&c.in,&readBytes);
	writtenBytes=myWrite(fd,arr,readBytes);
	free(arr);


	arr=myRead(fdsuffix,argv[4],8,&c.suf,&readBytes);
	writtenBytes=myWrite(fd,arr,readBytes);
	free(arr);

}

if(bytes<0) err(9,"error reading intervals from file");

close(fd);
close(fdaffix);
close(fdpostfix);
close(fdinfix);
close(fdprefix);
close(fdsuffix);

return 0;

}
