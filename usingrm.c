#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>




int main(int argc, char ** argv){

	if (argc < 2)
    {
        printf("%s","Need two arguments!");
        return 0;
    }

    else if (argc==2){

        if (strcmp(argv[1],"--version")==0){
            printf("%s","This is my custom rm with version 1.0.0\n");
            return 0;
        }
        

        if (strcmp(argv[1],"--help")==0){
            printf("%s"," 1) --version: to see the version of the rm function\n");
            printf("%s"," 2) -v: to see what is being done\n");

            return 0;
        }


        if (remove(argv[1])==0){
            printf("%s","FILE deleted successfully\n");
            return 0;
        }

        


    }

    else if (argc==3){
        if (strcmp(argv[1],"-v")==0){
            remove(argv[2]);
            printf("Removed using custom shell:%s\n",argv[2]);
        }

        if (strcmp(argv[1],"-f")==0){
            unlink(argv[2]);
        }
        
    }

    return 0;
}
