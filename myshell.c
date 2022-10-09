#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>


char ** parse(char * input){

	int noofbuffer = 100;
	char ** tokens = malloc(noofbuffer*sizeof(char *));
	int tokens_counter=0;



	int counttokenbuffer = 1024;

	char * current_token=(char *)malloc(counttokenbuffer*sizeof(char));

	int current_token_counter = 0;

    for (int i = 0; i < strlen(input); i++) {

    	char character = input[i];

        if (character == ' ') {

            if (tokens_counter + 1 > noofbuffer) {
                noofbuffer += 100;
                tokens = realloc(tokens, noofbuffer * sizeof(char*));

            }

            

            if (current_token_counter + 1 >= counttokenbuffer) {

                counttokenbuffer += 1024;

                current_token = realloc(current_token, counttokenbuffer);

            }

            tokens[tokens_counter] = current_token;
            tokens_counter++;

            current_token = malloc(counttokenbuffer * sizeof(char*));
            current_token_counter = 0;

        } else if (character == '\n') {

            if (tokens_counter + 2 > noofbuffer) {
                noofbuffer += 100;
                tokens = realloc(tokens, noofbuffer * sizeof(char*));

            }

            if (current_token_counter + 1 > counttokenbuffer) {
                counttokenbuffer += 1024;
                current_token = realloc(current_token, counttokenbuffer);

            }

            

            tokens[tokens_counter] = current_token;
            tokens_counter++;



            tokens[tokens_counter] = NULL;
            break;


        } else {

            if (current_token_counter + 1 > counttokenbuffer) {

                counttokenbuffer += 1024;
                current_token = realloc(current_token, counttokenbuffer);

            }

            current_token[current_token_counter] = character;
            current_token_counter++;

        }

    }

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
				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				printf("%s\n",buffpath);
				// strcat(buffpath,"/pwd");
				// execl(buffpath,buffpath,NULL,NULL,NULL);	

			}



			else if (strcmp(parsed[0],"ls")==0){

				strcat(home,"/ls");

				if (strcmp(parsed[1],"-l")==0 || strcmp(parsed[1],"-a")==0){
					execl(home,home,parsed[1],NULL,NULL);
				}
				else{
					execl(home,home,NULL,NULL,NULL);	
				}

			}



			else if (strcmp(parsed[0],"cat")==0){


				strcat(home,"/cat");

				execl(home,home,parsed[1],NULL,NULL);

			}
			
			else if (strcmp(parsed[0],"echo")==0){


				strcat(home,"/echo");

				if(strcmp(parsed[1],"-e")==0){
					execl(home,home,parsed[1],parsed[2],NULL);
				}

				else if (strcmp(parsed[1],"-n")==0){
					execl(home,home,parsed[1],parsed[2],NULL);
				}
				else{
					execl(home,home,parsed[1],NULL,NULL);
				}

				

			}

			else if (strcmp(parsed[0],"cd")==0){


				if (chdir(parsed[1])!=0){
					printf("%s","error occured!");
				}
				// execl("/home/parthiv9221/Desktop/Assignment2/cd","/home/parthiv9221/Desktop/Assignment2/cd",parsed[1],NULL,NULL);
			}

			else if (strcmp(parsed[0],"date")==0){


				strcat(home,"/date");


				if(strcmp(parsed[1],"+%B")==0 || strcmp(parsed[1],"+%Y")==0){

					execl(home,home,parsed[1],NULL,NULL);
				}
				else{
					execl(home,home,NULL,NULL,NULL);	
				}
				
			}

			else if (strcmp(parsed[0],"mkdir")==0){

				strcat(home,"/mkdir");

				if (strcmp(parsed[1],"-p")==0 || strcmp(parsed[1],"-v")==0){
					execl(home,home,parsed[1],parsed[2],NULL);	
				}
				else{
					execl(home,home,parsed[1],NULL,NULL);
				}
			}

			else if (strcmp(parsed[0],"rm")==0){


				strcat(home,"/rm");

				if (strcmp(parsed[1],"-v")==0){
					execl(home,home,parsed[1],parsed[2],NULL);
				}
				else{
					execl(home,home,parsed[1],NULL,NULL);	
				}

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

