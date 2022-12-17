 #include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>


#define socket_name "/tmp/Q2_socket"
#define buffer_size 100

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

    struct sockaddr_un addr;
    int data_socket;

    char buffer[buffer_size];


    if ((data_socket=socket(AF_UNIX,SOCK_STREAM,0))<0){
        perror("failed to create the socket on client");
        exit(1);
    }    

     memset(&addr,0,sizeof(struct sockaddr_un));

     addr.sun_family=AF_UNIX;

     strncpy(addr.sun_path,socket_name,sizeof(addr.sun_path)-1);


    

     if ((connect(data_socket,(struct sockaddr*)&addr,sizeof(struct sockaddr_un)))<0){
        perror("could not connect");
        exit(1);
     }



    int ret_from_server;
    int i=0;
    
    char arr[50];
    int j;

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

    while (i<50)
    {
        j=i;
        while (j<i+5){

            random_string_generate(arr);
            int index_to_be_send=j;
            send(data_socket,arr,50,0);
            send(data_socket,&index_to_be_send,sizeof(int),0);
            j++;
        }

        recv(data_socket,&ret_from_server,sizeof(int),0);
        printf("Highest index send by the server is: %d\n",ret_from_server);
        i=ret_from_server+1;
    }

    clock_gettime(CLOCK_REALTIME,&EndTime);
	float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    printf("total time taken is: %f\n",time);

    
    close(data_socket);


    return 0;
}



