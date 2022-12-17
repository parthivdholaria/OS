#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

char * alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


char * random_string_generate(int len){

    char * temp = (char *) malloc ((len+1)*sizeof(char));
    for (int j = 0; j < len; j++)
    {
        temp[j]=alphabets[rand()%sizeof(alphabets)];
    }
    temp[7]='\0';
    return temp;

}


int main(int argc, char const *argv[])
{
    
    int send_wala_fd,recv_wala_fd;
    int recieved_number;


    int fd;
    if ((fd=mkfifo("fifo_q2",0777))<0){
        perror("failed to create fifo");
        exit(1);
    }

    char * arr_strings[50];

    for (int i = 0; i < 50; i++)
    {
        arr_strings[i]=random_string_generate(7);
    }
    
    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

    //char arr[8];
    int i=0;
    int j;
    while (i<50){
        send_wala_fd = open("fifo_q2",O_WRONLY,0777);

        j=i;
        while (j<i+5){

            write(send_wala_fd,&j,4);  

            if ((write(send_wala_fd,arr_strings[j],8*sizeof(char)))<0){
                perror("failed to write by sender");
                exit(2);
            }
            
            j++;
        }
        close(send_wala_fd);
        // i=i+5;


        recv_wala_fd = open("fifo_q2",O_RDONLY);

        if ((read(recv_wala_fd,&recieved_number,sizeof(recieved_number)))<0){
            perror("failed to read from client!");
            exit(3);
        }

        printf("Highest ID recieved by client: %d\n",recieved_number);       
        i=recieved_number+1;
        close(recv_wala_fd);

    }

    clock_gettime(CLOCK_REALTIME,&EndTime);
	float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    printf("total time taken is: %f\n",time);

    unlink("fifo_q2");

    return 0;
}
