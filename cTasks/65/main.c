#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){

	if(argc==1){

		char buff;
		int bytes;
		while((bytes=read(0,&buff,sizeof(buff)))>0){
		
			if(write(1,&buff,sizeof(buff))<0){
				err(2,"error writing");
			}
		}

		if(bytes<0){
			err(3,"error reading");
		}
	}
	else{

		for(ssize_t i=1;i<argc;i++){

			char buf;
			if(strcmp("-",argv[i])==0){
				while(read(0,&buf,sizeof(buf))){
					
				if(write(1,&buf,sizeof(buf))<0){
				
					err(5,"error writing");
				}
							}
		}
			else{
				int fd=open(argv[i],O_RDONLY);
				if(fd<0){
					err(6,"error opening file");
				}
				char b;
				while(read(fd,&b,sizeof(b))>0){
					if(write(0,&b,sizeof(b))<0){
						err(7,"error writing");
					}
				}

					close(fd);

		}
		}
	}
}
