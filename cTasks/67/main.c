#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

int comp(const void *a, const void *b){

	uint32_t n1=*(const uint32_t*)a;
	uint32_t n2=*(const uint32_t*)b;

	if(n1<n2){
		return -1;
	}else if(n2>n1){
		return 1;
	}

	return 0;
}

int main(int argc,char** argv){

	if(argc!=3){
		errx(1,"invalid count of arg");
	}

	int fd=open(argv[1],O_RDONLY);
	if(fd<0){
		err(2,"error opening file");
	}

	struct stat st;

	if(stat(argv[1],&st)<0){
		err(3,"error stat file");
	}
	if(st.st_size % sizeof(uint32_t)!=0){
		errx(4,"invalid format");
	}
	if(st.st_size/sizeof(uint32_t)>4194304){
		errx(6,"too big file");
	}

	int fdOut=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU);
	if(fdOut<0){
		err(7,"error opening output file");
	}

	uint32_t* arr;
	ssize_t index=0;
	while(read(fd,&arr[index],sizeof(arr[index]))>0){
		index++;
	}

	for(int i=0;i<index;i++){
		printf("%d",arr[i]);
	}
	qsort((void*)arr,index,sizeof(arr[0]),comp);

	for(int i=0;i<index;i++){
		printf("%d",arr[i]);
	}
	int i=0;
	while(write(fdOut,&arr[i],sizeof(arr[i]))>0){
		i++;
	}

	exit(0);
}
