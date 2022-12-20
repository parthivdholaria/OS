#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


int ctr=0;

#define bowl_count 2

#define count 5

pthread_t thread_arr[5];


struct philosopher {
    int pos;
};

void philosopher_thinks(struct philosopher * philosopher){

    printf("philosopher %d is thinking\n",philosopher->pos+1);
 

}


void philosopher_eats(struct philosopher * philosopher){
    printf("philosopoher %d has picked up the bowl\n",philosopher->pos+1);
    printf("philosopher %d is eating\n",philosopher->pos+1);
    

}


void philosopher_takesfork(struct philosopher * philosopher){


    printf("philosopher %d picked up the forks %d and %d\n",philosopher->pos+1,(philosopher->pos+4+1)%5,(philosopher->pos+1)%5);     
    ctr++;
    


}


void philosopher_puts_back_fork(struct philosopher * philosopher){


    printf("philosopher %d has placed the forks %d and %d\n",philosopher->pos+1,(philosopher->pos+5)%5,(philosopher->pos+1)%5);   
    printf("philospher %d has placed the bowl\n",philosopher->pos+1);
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
        struct philosopher * philosopher = (struct philosopher *) malloc (sizeof(struct philosopher));
        philosopher->pos=i%count;

        struct philosopher * philosopher2 = (struct philosopher *) malloc (sizeof(struct philosopher));
        philosopher2->pos=(i+2)%count;

        pthread_create(&thread_arr[i%count],NULL,philosopher_utility,(void *)philosopher);
        pthread_create(&thread_arr[(i+2)%count],NULL,philosopher_utility,(void *)philosopher2);
        pthread_join(thread_arr[i%count],NULL);
        pthread_join(thread_arr[(i+2)%count],NULL);

    }



    printf("total times eaten by all 5 philospher once: %d\n",ctr);


    return 0;
}