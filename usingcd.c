#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>


int main(int argc, char * argv[]){
    char path[1000];
    chdir("..");
    printf("%s\n",getcwd(s,100));
    return 0;
}
