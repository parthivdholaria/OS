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


	while (1){


		printf("Parthiv@Custom>>");

		char * input=read_command();

		char ** parsed = parse(input);

		int rc = fork();



		if (rc!=0){

			wait(NULL);

		}



		else{



			if(strcmp(parsed[0],"pwd")==0){			
				strcat(home,"/pwd");
				execl(home,home,parsed[1],NULL,NULL);


			}



			else if (strcmp(parsed[0],"ls")==0){
		
				strcat(home,"/ls");
				execl(home,home,parsed[1],NULL,NULL);


			}


			else if (strcmp(parsed[0],"cat")==0){


				strcat(home,"/cat");

				execl(home,home,parsed[1],NULL,NULL);

			}
			
			else if (strcmp(parsed[0],"echo")==0){


				strcat(home,"/echo");
				execl(home,home,parsed[1],parsed[2],NULL);
				

			}

			else if (strcmp(parsed[0],"cd")==0){

				if (chdir(parsed[1])!=0){
					printf("%s","error occured!");
				}
			}

			else if (strcmp(parsed[0],"date")==0){


				strcat(home,"/date");
				execl(home,home,parsed[1],NULL,NULL);

				
			}

			else if (strcmp(parsed[0],"mkdir")==0){

				strcat(home,"/mkdir");
				execl(home,home,parsed[1],parsed[2],NULL);	

			}

			else if (strcmp(parsed[0],"rm")==0){


				strcat(home,"/rm");
				execl(home,home,parsed[1],parsed[2],NULL);	

			}

			else if (strcmp(parsed[0],"clear")==0){

				strcat(home,"/clear");
				execl(home,home,NULL,NULL,NULL);	
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

