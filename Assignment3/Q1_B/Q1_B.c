#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<time.h>


int main(){


	char path[100];
	getcwd(path,sizeof(path));


	int rc1,rc2,rc3;
	float time;

	struct timespec StartTime, EndTime;
	clock_gettime(CLOCK_REALTIME,&StartTime);

	rc1=fork();


	if (rc1==0){
		strcat(path,"/processA.sh");
		execl(path,"processA.sh",NULL,NULL,NULL);
	}
	else if (rc1>0){	
		wait(NULL);
		clock_gettime(CLOCK_REALTIME,&EndTime);
		time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
		printf("%f\n",time);

	}
	else{printf("%s\n","Error");}


	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc2=fork();

	if (rc2==0){
	
		//if the file is not being called then probably error in path (maybe it is being modified)
		strcat(path,"/processB.sh");
		execl(path,"processB.sh",NULL,NULL,NULL);
	}

	else if (rc2>0){
	
		wait(NULL);
        clock_gettime(CLOCK_REALTIME,&EndTime);
		time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
		printf("%f\n",time);
	
	}

	else{printf("%s\n","error");}


	clock_gettime(CLOCK_REALTIME,&StartTime);
	rc3=fork();

	if (rc3==0){
	
		strcat(path,"/processC.sh");
		execl(path,"processC.sh",NULL,NULL,NULL);
	}

	else if (rc3>0){
		
		wait(NULL);
        clock_gettime(CLOCK_REALTIME,&EndTime);
		time = (EndTime.tv_sec-StartTime.tv_sec)+(EndTime.tv_nsec-StartTime.tv_nsec)/1e9;
		printf("%f\n",time);
	
	}

	else{printf("%s\n","error!");}


	return 0;

}
