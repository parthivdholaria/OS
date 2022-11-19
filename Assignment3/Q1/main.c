#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void countA(){

	long long int count=0;

	long long int i;

	for (i = 0; i < pow(2,32); ++i)
	{
		count++;
	}


}

void countB(){

	long long int count=0;

	long long int i;

	for (i = 0; i < pow(2,32); ++i)
	{
		count++;
	}

}




void countC(){

	long long int count=0;

	long long int i;

	for (i = 0; i < pow(2,32); ++i)
	{
		count++;
	}

}


void* f_A(){

	// int priority = atoi(arg);


    FILE *fptr=fopen("TimeDataA1.txt","a");

    // struct sched_param param;
	// param.sched_priority=priority;
	// int ret=pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);
	countA();
    clock_gettime(CLOCK_REALTIME,&EndTime);
	float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    fprintf(fptr,"o %f\n",time);

    fclose(fptr);

	return NULL;


}


void * f_B(){


	// int priority = atoi(arg);
	


    FILE *fptr=fopen("TimeDataA1.txt","a");


    // struct sched_param param;
	// param.sched_priority=priority;
	// int ret=pthread_setschedparam(pthread_self(),SCHED_RR,&param);

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);
	countB();
    clock_gettime(CLOCK_REALTIME,&EndTime);
	float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    fprintf(fptr,"r %f\n",time);
    fclose(fptr);

	return NULL;


}

void * f_C(){

	// int priority = atoi(arg);
	


    FILE *fptr=fopen("TimeDataA1.txt","a");

    // struct sched_param param;
	// param.sched_priority=priority;
	// int ret=pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);

    struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);
	countC();
    clock_gettime(CLOCK_REALTIME,&EndTime);
	float time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
    fprintf(fptr,"f %f\n",time);
    fclose(fptr);

	return NULL;


}



int main()
{

    FILE * fptr=fopen("TimeDataA1.txt","w");
	fclose(fptr);

    pthread_t t1,t2,t3;
    int rc1,rc2,rc3;

	struct sched_param param1;
	param1.sched_priority=0;

	struct sched_param param2;
	param2.sched_priority=0;

	struct sched_param param3;
	param3.sched_priority=0;


	pthread_setschedparam(t1,SCHED_OTHER,&param1);
	pthread_setschedparam(t2,SCHED_RR,&param2);
	pthread_setschedparam(t3,SCHED_FIFO,&param3);




    for (int i = 1; i < 11; i++)
    {

		
        rc1=pthread_create(&t1,NULL,f_A,NULL);
        rc2=pthread_create(&t2,NULL,f_B,NULL);
        rc3=pthread_create(&t3,NULL,f_C,NULL);

        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_join(t3,NULL);



    }

    int rc=fork();

	if (rc==0){
		system("./A1.sh");
	}
	else if (rc>0){
		wait(NULL);
	}
	else{
		printf("Error loading file\n");
	}
    

    return 0;
}
