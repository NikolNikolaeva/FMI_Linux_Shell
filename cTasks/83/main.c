#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){

	if(argc==2){
	
		if(strlen(argv[1])>4) errx(1,"Command could not be longer than 4 chars");

		char buff[5];
		while(


	}
	if(argc==1){

		char* command="echo";

	}

}
