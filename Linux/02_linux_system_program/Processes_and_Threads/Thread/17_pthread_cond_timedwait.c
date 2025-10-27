#include<54func.h>
int main(int argc,char *argv[]){
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond =PTHREAD_COND_INITIALIZER;
    struct timeval now;
    gettimeofday(&now,NULL);
    printf("before,sec = %ld ,usec=%ld\n",now.tv_sec,now.tv_usec);
    struct timespec abstime;
    abstime.tv_sec=now.tv_sec+5;
    abstime.tv_nsec=0;
    
    pthread_cond_timedwait(&cond,&mutex,&abstime);
    gettimeofday(&now,NULL);
    printf("wake up,sec = %ld ,usec=%ld\n",now.tv_sec,now.tv_usec);
    return 0;
}