#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
int main(int argc, char const *argv[])
{

    FILE *fptr;
    fptr = fopen("Q1_B_TimeReport.txt", "a");

    char path[100];
    getcwd(path, sizeof(path));

    pid_t rc1, rc2, rc3, waitid;
    float time;

    struct timespec StartTime1, EndTime1, StartTime2, EndTime2, StartTime3, EndTime3;

    clock_gettime(CLOCK_REALTIME, &StartTime1);

    rc1 = fork();

    if (rc1 == 0)
    {

        struct sched_param p1;
        sched_setscheduler(rc1, SCHED_OTHER, &p1);
        strcat(path, "/processA.sh");
        execl(path, "processA.sh", NULL, NULL, NULL);
    }
    else if (rc1 > 0)
    {

        clock_gettime(CLOCK_REALTIME, &StartTime2);

        rc2 = fork();

        if (rc2 == 0)
        {
          struct sched_param p2;
            sched_setscheduler(rc2, SCHED_RR, &p2);
            strcat(path, "/processB.sh");
            execl(path, "processB.sh", NULL, NULL, NULL);
        }
        else if (rc2 > 0)
        {

            clock_gettime(CLOCK_REALTIME, &StartTime3);

            rc3 = fork();

            if (rc3 == 0)
            {
              	struct sched_param p3;
                sched_setscheduler(rc3, SCHED_FIFO, &p3);
                strcat(path, "/processC.sh");
                execl(path, "processC.sh", NULL, NULL, NULL);
            }

            else if (rc3 > 0)
            {
            }
        }
    }

    waitid = waitpid(-1, NULL, 0);

    while (waitid != -1)
    {
        if (waitid == rc1 && waitid!=rc2 && waitid!=rc3)
        {
            clock_gettime(CLOCK_REALTIME, &EndTime1);
        }
        else if (waitid == rc2 && waitid!=rc1 && waitid!=rc3)
        {
            clock_gettime(CLOCK_REALTIME, &EndTime2);
        }
        else if (waitid == rc3 && waitid!=rc1 && waitid!=rc2)
        {
            clock_gettime(CLOCK_REALTIME, &EndTime3);
        }

         waitid = waitpid(-1, NULL, 0);
        
    }

    time = (EndTime1.tv_sec - StartTime1.tv_sec) + (EndTime1.tv_nsec - StartTime1.tv_nsec) / 1e9;
    printf("OTHER %f\n", time);
    fprintf(fptr, "%f\n", time);

    time = (EndTime2.tv_sec - StartTime2.tv_sec) + (EndTime2.tv_nsec - StartTime2.tv_nsec) / 1e9;
    printf("RR %f\n", time);
    fprintf(fptr, "%f\n", time);

    time = (EndTime3.tv_sec - StartTime3.tv_sec) + (EndTime3.tv_nsec - StartTime3.tv_nsec)/1e9;
    printf("FIFO %f\n", time);
    fprintf(fptr, "%f\n", time);

    fclose(fptr);

    

    return 0;
}
