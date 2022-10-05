#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat>


int main(int argc,char * argv[]){

	if (argc<=1){
		printf("Few arguments given give atleast 2 arguments!")
		return 0;
	}

	else if (argc==2){
		char * directory=argv[1];

		int ret=mkdir(directory,0777);

		if (ret==-1){
			printf("Failed to create to directory!")
			return 0;
		}
	}




	return 0;
}