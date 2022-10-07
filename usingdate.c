#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
int main(int argc, char *argv[])
{

	if (argc==1){
		time_t t ;
	    char mytime[100];
	    time( &t );
	     
	    struct tm *tmp = localtime( &t );
	     
	    // using strftime to display time
	    strftime(mytime, sizeof(mytime), "%A %d %B %Y %I:%M:%S %p", tmp);
	     
	    printf("%s\n", mytime);
	}

	else if (argc==2){
		if (strcmp(argv[1],"+%B")==0){
			time_t t ;
		    char mytime[100];
		    time( &t );
		     
		    struct tm *tmp = localtime( &t );
		     
		    // using strftime to display time
		    strftime(mytime, sizeof(mytime), "%B", tmp);
		     
		    printf("%s\n", mytime);
		}

		else if (strcmp(argv[1],"+%Y")==0){
			time_t t ;
		    char mytime[100];
		    time( &t );
		     
		    struct tm *tmp = localtime( &t );
		     
		    // using strftime to display time
		    strftime(mytime, sizeof(mytime), "%Y", tmp);
		     
		    printf("%s\n", mytime);
		}
	}

	
	return 0;
}
