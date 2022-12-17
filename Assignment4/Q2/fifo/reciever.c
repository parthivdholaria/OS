#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    
    int recv_wala_fd;
    int send_wala_fd;
    int recvieved_number;
    int fd;

    int i=50;
    int largeindex;
    while (i>0)
    {
        recv_wala_fd = open("fifo_q2",O_RDONLY);

        int j=0;
        while (j<5)
        {

            read(recv_wala_fd,&recvieved_number,4);
            largeindex=recvieved_number;
            printf("%d ",recvieved_number);

            char * buffer = (char *) malloc (8*sizeof(char));
            read(recv_wala_fd,buffer,sizeof(char)*8);
            printf("%s\n",buffer);

            j++;
        }

        close(recv_wala_fd);

        send_wala_fd=open("fifo_q2",O_WRONLY);
        write(send_wala_fd,&largeindex,4);
        close(send_wala_fd);

        i=i-5;
    }

    unlink("fifo_q2");
    
    

    return 0;
}
