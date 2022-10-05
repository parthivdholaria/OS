#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
//#include <dir.h>


int main(int argc, char * argv[]){
    


	if (argc==1){
		printf("%s","Need two arguments\n");
		return 0;
	}

	else if (argc>2){
		printf("%s","Need only two arguments!");
		return 0;
	}

	else{
		char path[1000];
		char abspath[1000]="/home/parthiv9221/Desktop/Assignment2/";
		strcat(abspath, argv[1]);
	    chdir(abspath);
		printf("%s\n",getcwd(path,1000));
	}



    return 0;
}

