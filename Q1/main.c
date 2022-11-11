#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>


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



// clock start

// thread  create calls f()
// f_sched_other()
// sets the scheduling
// calls countA()

// clockend ends

//store the return values



void * f_A_RR(void * arg){

	pthread_t t1;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t1,SCHED_RR,&param);

	countA();

	return NULL;

}

void * f_A_OTHER(void * arg){

	pthread_t t1;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t1,SCHED_OTHER,&param);

	countA();

	return NULL;

}

void * f_A_FIFO(void * arg){

	pthread_t t1;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t1,SCHED_FIFO,&param);

	countA();

	return NULL;

}

void * f_B_RR(void * arg){

	pthread_t t2;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t2,SCHED_RR,&param);

	countB();

	return NULL;

}

void * f_B_OTHER(void * arg){

	pthread_t t2;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t2,SCHED_OTHER,&param);

	countB();

	return NULL;

}

void * f_B_FIFO(void * arg){

	pthread_t t2;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t2,SCHED_FIFO,&param);

	countB();

	return NULL;

}


void * f_C_RR(void * arg){

	pthread_t t3;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t3,SCHED_RR,&param);

	countC();

	return NULL;

}

void * f_C_OTHER(void * arg){

	pthread_t t3;
	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t3,SCHED_OTHER,&param);

	countC();

	return NULL;

}

void * f_C_FIFO(void * arg){

	pthread_t t3;

	int ret;
	
	struct sched_param param;
	param.sched_priority=0;
	ret=pthread_setschedparam(t3,SCHED_FIFO,&param);

	countC();

	return NULL;

}




int main(int argc, char const *argv[])
{


	float arr1[3];
	float arr2[3];
	float arr3[3];
	
	pthread_t t1,t2,t3;
	int rc1,rc2,rc3;

	float time;

	//1
	struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc1=pthread_create(&t1,NULL,f_A_OTHER,NULL);
	pthread_join(t1,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr1[0]=time;

	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc2=pthread_create(&t2,NULL,f_B_RR,NULL);
	pthread_join(t2,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr2[0]=time;

	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc3=pthread_create(&t3,NULL,f_C_FIFO,NULL);
	pthread_join(t3,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr3[0]=time;


	//2
	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc1=pthread_create(&t1,NULL,f_A_RR,NULL);
	pthread_join(t1,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr1[1]=time;

	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc2=pthread_create(&t2,NULL,f_B_FIFO,NULL);
	pthread_join(t2,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr2[1]=time;

	
	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc3=pthread_create(&t3,NULL,f_C_OTHER,NULL);
	pthread_join(t3,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr3[1]=time;

	//3
	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc1=pthread_create(&t1,NULL,f_A_FIFO,NULL);
	pthread_join(t1,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr1[2]=time;

	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc2=pthread_create(&t2,NULL,f_B_OTHER,NULL);
	pthread_join(t2,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr2[2]=time;

	
	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc3=pthread_create(&t3,NULL,f_C_RR,NULL);
	pthread_join(t3,NULL);
	clock_gettime(CLOCK_REALTIME,&EndTime);
	time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
	arr3[2]=time;




	FILE * fptr;

	fptr=fopen("TimeDataA1.txt","w");

	for(int i=0;i<3;i++){
		fprintf(fptr,"%f ",arr1[i]);
	}

	fprintf(fptr,"\n");
	for(int i=0;i<3;i++){
		fprintf(fptr,"%f ",arr2[i]);
	}
	fprintf(fptr,"\n");

	for(int i=0;i<3;i++){
		fprintf(fptr,"%f ",arr3[i]);
	}
	fprintf(fptr,"\n");


	fclose(fptr);



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
