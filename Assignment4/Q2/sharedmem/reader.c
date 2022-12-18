#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    int bytes_to_be_sent=1024;
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

    if ((shared_mem_fd2=shm_open("parthiv2",O_RDWR|O_CREAT,0777))<0){
        perror("error in opening shared memory1");
        exit(1);
    }

    ftruncate(shared_mem_fd2,bytes_to_be_sent);

    

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

    int i=50;
    int j;

    while (i>0)
    {
        j=i;

        while (j<i+5)
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
            sleep(2);

        }

        int largest=50-i+4;
        if ((shared_mem_ptr2=mmap(NULL,bytes_to_be_sent, PROT_WRITE,MAP_SHARED,shared_mem_fd2,0))<0){
                perror("error in mmap1");
                exit(3);
        }
        char int_to_str[5];
        sprintf(int_to_str,"%d",largest);
        memcpy(shared_mem_ptr2,int_to_str,sizeof(int_to_str));
        sleep(2);
    
    
        i-=5;
        
    }

    clock_gettime(CLOCK_REALTIME,&EndTime);
    float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    printf("total time taken is: %f\n",time-120);
    

    close(shared_mem_fd);
    shm_unlink("parthiv");


    return 0;
}
