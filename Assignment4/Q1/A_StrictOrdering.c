#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


int ctr=0;


#define count 5
sem_t fork_arr[5];
pthread_t thread_arr[5];

struct philosopher {
    sem_t *leftfork;
    sem_t *rightfork;
    int pos;
};

void philosopher_thinks(struct philosopher * philosopher){

    printf("philosopher %d is thinking\n",philosopher->pos+1);
 

}


void philosopher_eats(struct philosopher * philosopher){

    printf("philosopher %d is eating\n",philosopher->pos+1);

}


void philosopher_takesfork(struct philosopher * philosopher){

    
    sem_wait(philosopher->leftfork);
    sem_wait(philosopher->rightfork);
    printf("philosopher %d picked up the forks %d and %d\n",philosopher->pos+1,(philosopher->pos+4+1)%5,(philosopher->pos+1)%5);   
    ctr++;
    


}


void philosopher_puts_back_fork(struct philosopher * philosopher){

    sem_post(philosopher->leftfork);
    sem_post(philosopher->rightfork);
    printf("philosopher %d has placed the forks %d and %d\n",philosopher->pos+1,(philosopher->pos+5)%5,(philosopher->pos+1)%5);   

}




void * philosopher_utility(void * arg){

    struct philosopher * philosopher = (struct philosopher *)arg;

    
    philosopher_thinks(philosopher);
    philosopher_takesfork(philosopher);
    philosopher_eats(philosopher);
    philosopher_puts_back_fork(philosopher);
    

    return NULL;
}



int main(int argc, char const *argv[])
{
    
    for (int i = 0; i < 5; i++)
    {
        sem_init(&fork_arr[i],0,1);

    }

    for (int i = 0; i < 5; i++)
    {
        struct philosopher * philosopher = (struct philosopher *) malloc (sizeof(struct philosopher));
        philosopher->pos=i;
        philosopher->leftfork=&fork_arr[i];
        philosopher->rightfork=&fork_arr[(i+1)%5];

        pthread_create(&thread_arr[i],NULL,philosopher_utility,(void *)philosopher);
    }

    pthread_join(thread_arr[0],NULL);
    pthread_join(thread_arr[1],NULL);
    pthread_join(thread_arr[2],NULL);
    pthread_join(thread_arr[3],NULL);
    pthread_join(thread_arr[4],NULL);



    printf("total times eaten by all 5 philospher once: %d\n",ctr);


    return 0;
}
