#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

char * alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


void random_string_generate(char * temp){

    // char * temp=(char*) malloc ((len+1)*(sizeof(char)));

    for (int j = 0; j < 7; j++)
    {
        temp[j]=alphabets[rand()%sizeof(alphabets)];
    }
    temp[7]='\0';

}



#define shared_mem_name "os assignment 3"

int main(int argc, char const *argv[])
{
    int bytes_to_be_sent=512;
    int shared_mem_fd;
    void * shared_mem_ptr;
    char arr[50];


    if ((shared_mem_fd=shm_open("parthiv",O_RDWR|O_CREAT,0777))<0){
        perror("error in opening shared memory");
        exit(1);
    }

    ftruncate(shared_mem_fd,bytes_to_be_sent);

    if ((shared_mem_ptr=mmap(NULL,bytes_to_be_sent, PROT_WRITE,MAP_SHARED,shared_mem_fd,0))<0);

    char message[50];
    int index_to_sent;
    int i=0;
    while (i<50)
    {
        int j=i;
        while (j<i+5){
            random_string_generate(message);
            index_to_sent=j;

        }
    }
    






    return 0;
}
