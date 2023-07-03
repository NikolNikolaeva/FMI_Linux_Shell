#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc!=3)
	{
		errx(1,"Invalid count of arguments");
	}

	int fd1=open(argv[1], O_RDONLY);
	
	if(fd1<0){
		err(1,"ERORR: could not open file %s",argv[1]);
	}

	int fd2=open(argv[2],O_CREAT|O_RDWR);

	if(fd2<0)
	{
		err(2,"ERORR: opening file %s",argv[2]);
	}

	char bytes;
	while(read(fd1,&bytes, 1)>0)
	{
		write(fd2,&bytes,1);
	}

	if(bytes<0)
	{
		err(4,"ERORR: reading from file");
	}

	close(fd1);
	close(fd2);
	return 0;
}



