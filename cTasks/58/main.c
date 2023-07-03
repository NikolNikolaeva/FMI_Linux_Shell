#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
			
int main(int argc,char** argv){

	if(argc!=2){
		warnx("usage: %s <file>",argv[0]);
		errx(1,"Imvalid count of arg");
	}

	int fd=open(argv[1],O_RDWR);
	if(fd<0){
		err(2,"ERORR: opening file %s",argv[1]);
	}

	int arrChars[256]={0};

	char bytes;
	while(read(fd,&bytes,1)>0){
		arrChars[(int)bytes]++;
	}
			
			if(bytes<0){
			err(3,"ERORR: reading from file");
			}

			if(lseek(fd,0,SEEK_SET)<0){
				err(4,"ERORR: could not lseek fd");
			}

		for(int i=0;i<256;i++)
		{
			for(int j=0;j<arrChars[i];j++){
			
				if(write(fd,&i,1)<0){
					err(5,"ERORR: could not write in file");
				}
			}
		}
close(fd);
return 0;
}
