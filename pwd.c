#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int main(int argc, char ** argv){

	char bufferpath[100];

	if(argc>2){

		printf("%s ","Too many parameters");
		exit(10);
	}

	else if (argc==1){
		printf("%s\n",getcwd(bufferpath,sizeof(bufferpath)));
	}


	return 0;
}
