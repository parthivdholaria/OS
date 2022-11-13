#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>


#define TWOD_COPY_SYSCALL 451

bool checkContent(float* matrix_src, float* matri_dest, int m, int n)
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matri_dest[i*n+j] != matrix_src[i*n+j])
                return false;
        }

        printf("\n");
    }

    return true;
}

int main(int argc, char const *argv[])
{

    int r=3,c=5;


    float matrix_src[]={1.1,1.2,1.3,1.4,1.5,2.1,2.2,2.3,2.4,2.5,3.1,3.2,3.3,3.4,3.5};


    //float matrix_src[]={1.1,1.2,1.3,2.1,2.2,2.3,3.1,3.2,3.3};

    float matrix_dest[15];


    long sys_call_return_status;

    sys_call_return_status = syscall(451,matrix_src,matrix_dest,3,5);

    if (!sys_call_return_status)
    {
	
	for (int i=0;i<r;i++){
		for (int j=0;j<c;j++){
		
			printf("%f ",matrix_dest[i*c+j]);
		
		}

		printf("\n");
	
	}


        printf("%s\n", "The matrix has been successfully copied!");
        if (checkContent(matrix_src, matrix_dest, 3, 5))
        {
            printf("%s\n", "The content matches!");
        }
    }

    return 0;
}
