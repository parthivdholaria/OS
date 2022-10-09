#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>


#define splitters " \t\r\n\a"



char ** parse(char * cmmd){


	int buffsize=64;
	int pos=0;

	char ** tokens= (char **) malloc (buffsize*sizeof(char *));

	char * token;

	if (tokens==NULL){
		printf("Could not allocate memory\n");
		exit(1);
	}

	token = strtok(cmmd,splitters);

	while (token!=NULL){
		tokens[pos]=token;
		pos++;


		if (pos>=buffsize){
			buffsize+=64;
			tokens=realloc(tokens,buffsize*sizeof(char  *));
			if (tokens==NULL){
				printf("Could not allocate memory while reallocating \n");
				exit(1);
			}
		}

		token=strtok(NULL,splitters);

	}

	tokens[pos]=NULL;
	return tokens;

}





char * read_command(){

	char * buffer;
	size_t buffsize=1024;
	size_t line;



	buffer=(char*) malloc (buffsize*sizeof(char));



	if (buffer == NULL){
		printf("%s","Error coudl not allocate memory\n");
		exit(1);
	}

	line = getline(&buffer,&buffsize, stdin);

	return buffer;

}



int main(int argc, char * argv[]){



	char home[100];
	getcwd(home,sizeof(home));

	char * match1[]={"pwd","ls","date"};
	char * match2[]={"cat","echo","mkdir","rm"};


	while (1){


		printf("Parthiv@Custom>>");

		char * input=read_command();

		char ** parsed = parse(input);

		int rc = fork();



		if (rc!=0){

			wait(NULL);

		}



		else{

			if (strcmp(parsed[0],"cd")==0){
				if (chdir(parsed[1])!=0){
					printf("%s","error occured!");
				}
			}

			else if (strcmp(parsed[0],"clear")==0){

				strcat(home,"/clear");
				execl(home,home,NULL,NULL,NULL);	
			}

			else{
				for (int i=0;i<sizeof(match1)/sizeof(match1[0]);i++){
					if (strcmp(match1[i],parsed[0])==0){
						strcat(home,"/");
						strcat(home,parsed[0]);
						execl(home,home,parsed[1],NULL,NULL);

					}
				}

				for (int i=0;i<sizeof(match2)/sizeof(match2[0]);i++){
					if (strcmp(match2[i],parsed[0])==0){
						strcat(home,"/");
						strcat(home,parsed[0]);
						execl(home,home,parsed[1],parsed[2],NULL);

					}
				}
			}

		}

		if (strcmp(parsed[0],"exit")==0){

				break;

		}	

		free(input);
		free(parsed);

	}

	return 0;

}

