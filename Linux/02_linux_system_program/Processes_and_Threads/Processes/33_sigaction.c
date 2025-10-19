#include<54func.h>
void handler(int signum){
    printf("before signum = %d\n",signum);
    sleep(5);
    printf("after signum = %d\n",signum);
}
int main(int argc,char *argv[]){
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler=handler;
    sigaction(SIGINT,&act,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}