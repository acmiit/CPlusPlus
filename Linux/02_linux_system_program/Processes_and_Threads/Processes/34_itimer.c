#include<54func.h>
void handler(int signum){
    time_t now=time(NULL);
    printf("now = %s\n",ctime(&now));
}
int main(int argc,char *argv[]){
    signal(SIGALRM,handler);
    struct itimerval itimer;
    itimer.it_value.tv_sec=3;
    itimer.it_value.tv_usec=0;
    itimer.it_interval.tv_sec=1;
    itimer.it_interval.tv_usec=0;
    handler(0);
    setitimer(ITIMER_REAL,&itimer,NULL);
    while(1){

    }
    return 0;
}