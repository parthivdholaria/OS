#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char * argv[]){




	if (argc==2){
		
		FILE * fptr=fopen(argv[1],"r");

		if (!fptr){
			printf("%s","2 arguments needed! or file could not open\n");
			return 0;
		}
		char c;
		while ((c=fgetc(fptr))!=EOF){
			printf("%c",c);
		}

		fclose(fptr);
	}

	else if (argc==3){
		if (strcmp(argv[1],"-n")==0){
			
			FILE * file;

			file=fopen(argv[2],"r");
			if (!file){
				printf("%s no such file or directory\n",argv[2]);
			}
			else{
				int j=0;
				char line[1024];
				while (fgets(line,sizeof(line),file)){
						printf("%d %s",++j,line);
				}
				fclose(file);
			}




		}
		else if (strcmp(argv[1],">")==0){
			FILE * fptr=fopen(argv[2],"w");
			if (!fptr){
				printf("Could not create the file\n");
				return 0;
			}
			printf("File created successfully\n");
		}

		else if (strcmp(argv[1],"-E")==0){
			FILE * file;
			file=fopen(argv[2],"r");
			if (!file){
				printf("%s no such file or directory\n",argv[2]);
			}
			else{
				int j=0;
				char line[1024];
				while (fgets(line,sizeof(line),file)){
					line[strlen(line)-2]='$';
					printf("%s",line);
				}
				fclose(file);
			}

		}
	}
	 


	return 0;
}
