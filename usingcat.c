#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char * argv[]){

	 FILE * fptr=fopen(argv[1],"r");

	 if (argc!=2 || !fptr){
	 	printf("%s","2 arguments needed! or file could not open\n");
	 	return 0;
	 }

	 char c;
	 while ((c=fgetc(fptr))!=EOF){
	 	printf("%c",c);
	 }

	fclose(fptr);


	return 0;
}
