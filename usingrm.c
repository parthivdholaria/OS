#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include <unistd.h>


static int removeFiles(char * path, struct stat * sbuf, int type, struct FTW * ftwb){
	if (remove(path)<0){
		printf("%s","Could not delet the file");
		return -1;
	}

	return 0;
}




int main(int argc, char ** argv){

	if (argc != 2)
    {
        printf("%s","Need to two arguments!");
        return 0;
    }

    else if (argc==2){
    	if (nftw(argv[1],removeFiles, 10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS)<0){
    		printf("%s","Error in deleting your file");
    		return 0;
    	}
    }

    return 0;
}