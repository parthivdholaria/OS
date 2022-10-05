#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <dirent.h>

void ls(char * dir, int a, int l){
	DIR * currdir = opendir(dir);
	if (!currdir){
		printf("%s\n","Invalid command! Directory does not exist or Unable to read directory!");
		return;
	}

	struct dirent* entity;
	entity=readdir(currdir);


	while (entity!=NULL){

		if (!a && entity->d_name[0]=='.'){
			continue;
		}

		printf("%s  ",entity->d_name);
		
		if (l){
			printf("\n");
		}

		entity=readdir(currdir);

		
	}

	if (!l){
		printf("\n");
	}

	closedir(currdir);

}


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

			printf("%s  ",entity->d_name);
			entity=readdir(currdir);

		}
		printf("\n");

		closedir(currdir);
	}

	else if (argc==2){
		if (argv[1][0]=='-'){
			int a=0;
			int l=0;

			char * itr = (char *)(argv[1]+1);

			while (*itr){
				if (*itr=='a'){
					a=1;
				}

				else if (*itr=='l'){
					l=1;
				}

				else{
					printf("%s\n","Invalid input for the ls command!");
					return 0;
				}

				itr++;

			}

			ls(".",a,l);

			}
		}


	return 0;
}
