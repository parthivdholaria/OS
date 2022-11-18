#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>


#define TWOD_COPY_SYSCALL 451


int main(int argc, char const *argv[]) {


    int r=3,c=5;


    float matrix_src[3][5]={1.1,1.2,1.3,1.4,1.5,2.1,2.2,2.3,2.4,2.5,3.1,3.2,3.3,3.4,3.5};


    //float matrix_src[]={1.1,1.2,1.3,2.1,2.2,2.3,3.1,3.2,3.3};

    float matrix_dest[3][5];


    long sys_call_return_status;

    sys_call_return_status = syscall(451,matrix_src,matrix_dest,3,5);

    if (!sys_call_return_status)
    {
	
	for (int i=0;i<r;i++){
		for (int j=0;j<c;j++){
		
			printf("%f ",matrix_dest[i][j]);
		
		}

		printf("\n");
	
	}

        printf("%s\n", "The matrix has been successfully copied!");
	for (int i=0;i<r;i++){
		for (int j=0;j<c;j++){
			if (matrix_src[i][j] != matrix_dest[i][j])	
				printf("value mismatch : %f ",matrix_dest[i][j]);
		
		}

		printf("\n");
	}
    }

    return 0;
}
