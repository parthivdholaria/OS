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


int main(int argc, char const *argv[])
{
    
    struct sockaddr_un server_address;
    int socket_fd;
    char buffer[512];


    if (remove(socket_name)<0 && errno!=ENONET){
        perror("socket with the name /temp/Q2_socket already exist");
        exit(0);
    }

    if ((socket_fd=socket(AF_UNIX,SOCK_STREAM,0))<0){
        perror("failed to create the socket on server");
        exit(1);
    }    


    memset(&server_address, 0, sizeof(struct sockaddr_un));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, socket_name, sizeof(server_address.sun_path) - 1);


    if (bind(socket_fd,(struct sockaddr * )&server_address,sizeof(struct sockaddr_un))<0){
        perror("error in binding socket to the system");
        exit(2);
    }

    int lis;

    if ((lis=listen(socket_fd,10))<0){
        perror("error in listeing to the client");
        exit(3);
    }

    int ds = accept(socket_fd,NULL,NULL);

    int receievd_number;
    char recieved_string[50];

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

    int i=50;
    while (i>0)
    {
        int j=0;
        while (j<5)
        {
            recv(ds,recieved_string,50,0);
            recv(ds,&receievd_number,4,0);
            printf("%d %s\n",receievd_number,recieved_string);
            j++;
        }
        send(ds,&receievd_number,4,0);
        i-=5;
    }
    

    

    close(socket_fd);
    close(ds);



    return 0;
}
