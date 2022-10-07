#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc,char * argv[]){

	if (argc<=1){
		printf("Few arguments given give atleast 2 arguments!\n");
		return 0;
	}

	else if (argc==2){
		char * directory=argv[1];

		int ret=mkdir(directory,0777);

		if (ret==-1){
			printf("Failed to create to directory!\n");
			return 0;
		}
	}

	else if (argc==3){
		if (strcmp(argv[1],"-p")==0){
			char cmmd[100]="mkdir -p ";
			strcat(cmmd,argv[2]);
			system(cmmd);
			int ret=mkdir(argv[2],0777);
		}
		else if (strcmp(argv[1],"-v")==0){
			char * dir1=argv[2];

			int ret1=mkdir(dir1,0777);


			if (ret1==-1){
				printf("Failed to create to directory%s!\n",dir1);
				return 0;
			}
			else{
				printf("Custom mkdir: created a directory: %s\n",dir1);
			}

		}
	}




	return 0;
}
