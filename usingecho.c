#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char const *argv[])
{
	

	if (argc<=1){
		printf("Enter at least 2 arguments\n");
		return 0;
	}

	else if (argc==2){
	
		for (int i = 1; i < argc; ++i)
		{
			printf("%s", argv[i]);
		}
		printf("\n");
	}
	
	else if (argc==3){
		
	

		if (strcmp(argv[1],"-e")==0){
			
			execl("/bin/echo","/bin/echo","-e",argv[2],NULL);
		
		}
		else if (strcmp(argv[1],"-n")==0){
			
			execl("/bin/echo","/bin/echo","-n",argv[2],NULL);
		
		}
	}

	
	return 0;
}

