#include <stdio.h>
#include <sys/stat.h>
#include <err.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc,char** argv){

	if(argc<1){
		errx(1,"arg");
	}

	//bool option=strcmp("-n",argv[1])==0?true:false;

	//if(option){
	//	int line=1;
//
//		if(argc>2){
//			char buf;
//			for(int i=2;i<argc;i++){
//				int fd;
//				if(strcmp("-",argv[i])==0){
//					fd=0;
//				}else{
//					fd=open(argv[i],O_RDONLY);
//				}



//			}
//		}
//		else{
			char buff[1024];
		
			setbuf(stdout,buff);
			//write(1,&line,sizeof(line));
			fflush(stdout);
			//line++;
//		}
//	}
//	else{
//		if(argc>1){
//		
//			for(int i=1;i<argc;i++){

//				int fd;
//				if(strcmp(argv[i],"-")==0){
//					fd=0;
//				}
///				else{
//					fd=open(argv[i],O_RDONLY);
//				}
//				char buf;
//				while(read(fd,&buf,1)>0){
//					write(1,&buf,1);
//				}
//				close(fd);
//			}
//			
//		}
//		else{
//			char buf;
//			while(read(0,&buf,1)>0){
//				write(1,&buf,1);
//			}

//		}
	//}
}
