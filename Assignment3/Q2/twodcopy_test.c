#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

// the number 452 might be different for you must be checked
#define TWOD_COPY_SYSCALL 452

bool checkContent(float **matrix_src, float **matri_dest, int m, int n)
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

    float matrix_src[3][5] = {{1.1, 1.2, 1.3, 1.4, 1.5}, {2.1, 2.2, 2.3, 2.4, 2.5}, {3.1, 3.2, 3.3, 3.4, 3.5}};

    float matrix_dest[3][5];

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
