#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <pthread.h>


void * shared_mem_ptr;

int ctr=0;


char * alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


void random_string_generate(char * temp){

    // char * temp=(char*) malloc ((len+1)*(sizeof(char)));

    for (int j = 0; j < 7; j++)
    {
        temp[j]=alphabets[rand()%sizeof(alphabets)];
    }
    temp[7]='\0';

}


int main(int argc, char const *argv[])
{
    int bytes_to_be_sent=1024;
    int shared_mem_fd;
    void * shared_mem_ptr;
    char arr[50];

    int shared_mem_fd2;
    void * shared_mem_ptr2;


    sem_t * lock;

    shm_unlink("parthiv");

    if ((shared_mem_fd=shm_open("parthiv",O_RDWR|O_CREAT,0777))<0){
        perror("error in opening shared memory1");
        exit(1);
    }

    ftruncate(shared_mem_fd,bytes_to_be_sent);


    if ((shared_mem_ptr=mmap(NULL,bytes_to_be_sent, PROT_WRITE,MAP_SHARED,shared_mem_fd,0))<0){
        perror("error in mmap1");
        exit(3);
    }


    char message[8];
    int index_to_sent;
    int i=0;
    char int_to_string[5];

    // int shared_mem_fd2;
    // void * shared_mem_ptr2;
    struct stat stat_ptr2;

    if ((shared_mem_fd2=shm_open("parthiv2",O_RDWR|O_CREAT,0777))<0){
        perror("error in opening shared memory1");
        exit(1);
    }

    if ((fstat(shared_mem_fd2,&stat_ptr2))<0){
        perror("error in fstat");
        exit(2);
    }

    while (i<50)
    {
        lock = sem_open("sem_lock",O_CREAT,0777,0);
        int j=i;
        while (j<i+5){
            random_string_generate(message);
            index_to_sent=j;

            sprintf(int_to_string,"%d",index_to_sent);

            
            char str_to_be_send[10] = "";
            strcat(str_to_be_send,int_to_string);
            strcat(str_to_be_send," ");
            strcat(str_to_be_send,message);

            memcpy(shared_mem_ptr,str_to_be_send,15*sizeof(char));
            sleep(2);
            j++;

        }

        sem_post(lock);

        sleep(2);

        sem_wait(lock);


        if ((shared_mem_ptr2=mmap(NULL,bytes_to_be_sent, PROT_READ,MAP_SHARED,shared_mem_fd2,0))<0){
            perror("error in mmap");
            exit(3);
        }

        write(STDOUT_FILENO,shared_mem_ptr2,stat_ptr2.st_size);
        printf("\n");

        sem_post(lock);

        i=i+5;
    }

    return 0;
}
