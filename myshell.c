#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <unistd.h>

#include <sys/wait.h>




void type_prompt(){

	static bool first_time=true;

	if (first_time){

		const char* CLEAR_SCREEN_ANSI=" \e[1;1H\e[2J";

		write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);

		first_time=false;

	}



	printf("Parthiv@Custom>>");

}









char ** parse(char * input){

	int all_tokens_buffer = 100;

	char ** all_tokens = malloc(all_tokens_buffer*sizeof(char *));

	int all_tokens_counter=0;



	int current_token_buffer = 1024;

	char * current_token=malloc(current_token_buffer*sizeof(char));

	int current_token_counter = 0;

    for (int i = 0; i < strlen(input); i++) {



    	char character = input[i];



        if (character == ' ') {



            if (all_tokens_counter + 1 > all_tokens_buffer) {

                all_tokens_buffer += 100;

                all_tokens = realloc(all_tokens, all_tokens_buffer * sizeof(char*));

            }

            

            if (current_token_counter + 1 >= current_token_buffer) {

                current_token_buffer += 1024;

                current_token = realloc(current_token, current_token_buffer);

            }



            all_tokens[all_tokens_counter] = current_token;

            all_tokens_counter++;



            current_token = malloc(current_token_buffer * sizeof(char*));

            current_token_counter = 0;



        } else if (character == '\n') {

            

            if (all_tokens_counter + 2 > all_tokens_buffer) {

                all_tokens_buffer += 100;

                all_tokens = realloc(all_tokens, all_tokens_buffer * sizeof(char*));

            }



            if (current_token_counter + 1 > current_token_buffer) {

                current_token_buffer += 1024;

                current_token = realloc(current_token, current_token_buffer);

            }

            

            all_tokens[all_tokens_counter] = current_token;

            all_tokens_counter++;



            all_tokens[all_tokens_counter] = NULL;

            break;



        } else {



            if (current_token_counter + 1 > current_token_buffer) {

                current_token_buffer += 1024;

                current_token = realloc(current_token, current_token_buffer);

            }



            current_token[current_token_counter] = character;

            current_token_counter++;



        }



    }



    return all_tokens;	



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



	printf("Parthiv@Custom");

	printf("\n");





	while (1){



		type_prompt();

		char * input=read_command();



		char ** parsed = parse(input);



		// execute(parsed);





		int rc = fork();



		if (rc!=0){

			wait(NULL);

		}



		else{



			if(strcmp(parsed[0],"pwd")==0){
				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/pwd");
				execl(buffpath,buffpath,NULL,NULL,NULL);	

			}



			else if (strcmp(parsed[0],"ls")==0){

				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"ls");

				if (strcmp(parsed[1],"-l")==0 || strcmp(parsed[1],"-a")==0){
					execl(buffpath,buffpath,parsed[1],NULL,NULL);
				}
				else{
					execl(buffpath,buffpath,NULL,NULL,NULL);	
				}

			}



			else if (strcmp(parsed[0],"cat")==0){

				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/cat");

				execl(buffpath,buffpath,parsed[1],NULL,NULL);

			}
			
			else if (strcmp(parsed[0],"echo")==0){

				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/echo");

				if(strcmp(parsed[1],"-e")==0){
					execl(buffpath,buffpath,parsed[1],parsed[2],NULL);
				}

				else if (strcmp(parsed[1],"-n")==0){
					execl(buffpath,buffpath,parsed[1],parsed[2],NULL);
				}
				else{
					execl(buffpath,buffpath,parsed[1],NULL,NULL);
				}

				

			}

			else if (strcmp(parsed[0],"cd")==0){


				if (chdir(parsed[1])!=0){
					printf("%s","error occured!");
				}
				// execl("/home/parthiv9221/Desktop/Assignment2/cd","/home/parthiv9221/Desktop/Assignment2/cd",parsed[1],NULL,NULL);
			}

			else if (strcmp(parsed[0],"date")==0){

				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/date");


				if(strcmp(parsed[1],"+%B")==0 || strcmp(parsed[1],"+%Y")==0){

					execl(buffpath,buffpath,parsed[1],NULL,NULL);
				}
				else{
					execl(buffpath,buffpath,NULL,NULL,NULL);	
				}
				
			}

			else if (strcmp(parsed[0],"mkdir")==0){
				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/mkdir");

				if (strcmp(parsed[1],"-p")==0 || strcmp(parsed[1],"-v")==0){
					execl(buffpath,buffpath,parsed[1],parsed[2],NULL);	
				}
				else{
					execl(buffpath,buffpath,parsed[1],NULL,NULL);
				}
			}

			else if (strcmp(parsed[0],"rm")==0){

				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/rm");

				if (strcmp(parsed[1],"-v")==0){
					execl(buffpath,buffpath,parsed[1],parsed[2],NULL);
				}
				else{
					execl(buffpath,buffpath,parsed[1],NULL,NULL);	
				}

			}

			else if (strcmp(parsed[0],"clear")==0){
				char buffpath[100];
				getcwd(buffpath,sizeof(buffpath));
				strcat(buffpath,"/clear");
				execl(buffpath,buffpath,NULL,NULL,NULL);	
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

