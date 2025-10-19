#include<54func.h>
void handler(int signum){
    time_t now=time(NULL);
    printf("now = %s\n",ctime(&now));
}
int main(int argc,char *argv[]){
    signal(SIGVTALRM,handler);
    struct itimerval itimer;
    itimer.it_value.tv_sec=3;
    itimer.it_value.tv_usec=0;
    itimer.it_interval.tv_sec=1;
    itimer.it_interval.tv_usec=0;
    setitimer(ITIMER_VIRTUAL,&itimer,NULL);
    handler(0);

    while(1){

    }
    return 0;
}