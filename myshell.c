#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <pthread.h>


#define splitters " \t\r\n\a"



char ** parse(char * cmmd,int *count){


	int buffsize=128;
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
		token=strtok(NULL,splitters);

	}

	tokens[pos]=NULL;
	*count=pos;
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


void *execute_via_thread(void * arg){
	char * input=(char *)arg;
	system(input);
	return NULL;
}



int main(int argc, char * argv[]){


	static char home[100];
	getcwd(home,sizeof(home));



	while (1){


		printf("Parthiv@Custom>>");

		char * input=read_command();

		int flag=0;

		
		char filter[]="";
		for (int i=0;i<strlen(input);i++){
			if (input[i]=='&'){
				flag=1;
				break;
			}
			strncat(filter,&input[i],1);
		}

		int count=0;
		char ** parsed = parse(input,&count);
		static char bufferpath[100];


		if (strcmp(parsed[0],"exit")==0){

			exit(0);

		}


		if (flag){
			pthread_t p1;
			int rc;
			rc = pthread_create(&p1, NULL, execute_via_thread, filter); assert(rc==0);		
			rc=pthread_join(p1,NULL); assert(rc==0);
		}

		else{


			int rc = fork();



			if (rc!=0){

				wait(NULL);

			}

			else{
			
				char * match1[]={"ls","date"};
				char * match2[]={"cat","mkdir","rm"};

				if (strcmp(parsed[0],"cd")==0){

					if (strcmp("--help",parsed[1])==0){
							printf("%s","1) --help: to see the description of cd command\n");
							printf("%s","2) --version: to see the current version\n");

					}

					else if (strcmp("--version",parsed[1])==0){
						printf("%s","current version of custom cd is 1.0.1\n");
					}
					
					if (chdir(parsed[1])!=0){
						printf("%s","error occured!\n");
					}
				}


				else if (strcmp(parsed[0],"clear")==0){

					strcat(home,"/clear");
					execl(home,home,NULL,NULL,NULL);	
				}

				else if (strcmp(parsed[0],"pwd")==0 || strcmp(parsed[0],"echo")==0){

					if (strcmp(parsed[0],"pwd")==0){


						if (count==1){
							printf("%s\n",getcwd(bufferpath,sizeof(bufferpath)));
						}

						if (strcmp("--help",parsed[1])==0){
							printf("%s","1) --help: to see the description of pwd command\n");
							printf("%s","2) --version: to see the current version\n");

						}
						else if (strcmp("--version",parsed[1])==0){
							printf("%s","current version of custom pwd is 1.0.1\n");
						}

						else if (strcmp(parsed[1],"-L")==0){
							printf("%s\n",getcwd(bufferpath,sizeof(bufferpath)));

						}
						else if (strcmp(parsed[1],"-P")==0){
							printf("%s\n",getcwd(bufferpath,sizeof(bufferpath)));

						}
						else{
							printf("%s","Unhandled command\n");
						}
					}

					else if (strcmp("echo",parsed[0])==0){




						if (strcmp(parsed[1],"-n")==0){
							for (int i=2;i<count;i++){
								printf("%s ",parsed[i]);
							}
						}
						else if (strcmp(parsed[1],"--help")==0){
							printf("%s","1) --help: to see help regarding help/echo command\n");
							printf("%s","2) -n: used to avoid backslash n\n");
						}
						else if (count==2){
							for (int i = 1; i < count; ++i)
							{
								printf("%s", parsed[i]);
							}
							printf("\n");
						}
						else{
							printf("%s","Unhandled command\n");
						}

					}

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




		free(input);
		free(parsed);

		}
	
	}

	return 0;

}
