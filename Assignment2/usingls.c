#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(int argc,char *argv[]){

	

	if (argc==1){
		DIR * currdir = opendir(".");
		if (!currdir){
			printf("%s\n","Invalid command! Directory does not exist or Unable to read directory!");
			return 0;
		}


		struct dirent* entity;
		entity=readdir(currdir);


		while (entity!=NULL){

			if ( strcmp(entity->d_name,".")==0 || strcmp(entity->d_name,"..")==0){
				entity=readdir(currdir);
				continue;
			}

			printf("%s  ",entity->d_name);
			entity=readdir(currdir);

		}
		printf("\n");

		closedir(currdir);
	}

	else if (argc==2){

		DIR * currdir = opendir(".");

		if (currdir==NULL){
			printf("Could not Open the required directory!\n");
		}

		if (strcmp(argv[1],"-1")==0){

			struct dirent* entity;
			entity=readdir(currdir);
			while (entity!=NULL){

				if ( strcmp(entity->d_name,".")==0 || strcmp(entity->d_name,"..")==0){
					entity=readdir(currdir);
					continue;
				}

				printf("%s\n",entity->d_name);
				entity=readdir(currdir);

			}
			printf("\n");

		}

		else if (strcmp(argv[1],"-a")==0){
			
			struct dirent* entity;
			entity=readdir(currdir);


			while (entity!=NULL){

				printf("%s  ",entity->d_name);
				entity=readdir(currdir);

			}
			printf("\n");
		}

		else if (strcmp(argv[1],"-d")==0){
			printf("%s",".\n");
			return 0;
		}
		else{
			printf("%s","Entered a unhandled argument!\n");
		}

	}
		
	return 0;
}
