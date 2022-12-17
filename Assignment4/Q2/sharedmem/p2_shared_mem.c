#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int bytes_to_be_sent=512;
    int shared_mem_fd;
    int shared_mem_fd2;

    void * shared_mem_ptr;
    void * shared_mem_ptr2;

    char arr[50];
    struct stat stat_ptr;
    struct stat stat_ptr2;



    if ((shared_mem_fd=shm_open("parthiv",O_RDWR|O_CREAT,0777))<0){
        perror("error in opening shared memory");
        exit(1);
    }


    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

    int i=50;
    int j;

    while (i>0)
    {
        j=0;
        while (j<5)
        {
            
            if ((fstat(shared_mem_fd,&stat_ptr))<0){
                 perror("error in fstat");
                exit(2);
            }


            if ((shared_mem_ptr=mmap(NULL,bytes_to_be_sent, PROT_READ,MAP_SHARED,shared_mem_fd,0))<0){
                perror("error in mmap");
                exit(3);
            }

            write(STDOUT_FILENO,shared_mem_ptr,stat_ptr.st_size);
            printf("\n");


            j++;
        }
        i-=5;
        
    }

    clock_gettime(CLOCK_REALTIME,&EndTime);
    float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    printf("total time taken is: %f\n",time);
    

    close(shared_mem_fd);


    return 0;
}

