#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>



// the number 452 might be different for you must be checked
#define TWOD_COPY_SYSCALL 451

bool checkContent(float** matrix_src, float** matri_dest, int m, int n)
{

    // printing the content of the src_matrix

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", matri_dest[i][j]);
        }

        printf("\n");
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matri_dest[i][j] != matrix_src[i][j])
                return false;
        }

        printf("\n");
    }

    return true;
}

int main(int argc, char const *argv[])
{

    float ** matrix_src;

    matrix_src=(float**)malloc(3*sizeof(float*));

    for (int i=0;i<3;i++){
    	matrix_src[i]=(float*)malloc(5*sizeof(float));
    }

    for (int i=0;i<3;i++){
    
    	for (int j=0;j<5;j++){
	
		matrix_src[i][j]=i+j+0.1;
		
	}
    
    }



    float ** matrix_dest;

    matrix_dest=(float**)malloc(3*sizeof(float*));
	
	


    for (int i=0;i<3;i++){
    	
	    matrix_dest[i]=(float*)malloc(5*sizeof(float));
    
    }


    long sys_call_return_status;

    sys_call_return_status = syscall(TWOD_COPY_SYSCALL);

    if (sys_call_return_status != EFAULT)
    {

        printf("%s\n", "The matrix has been successfully copied!");
        if (checkContent(matrix_src, matrix_dest, 3, 5))
        {
            printf("%s\n", "The content matches!");
        }
    }

    return 0;
}
