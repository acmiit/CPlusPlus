#include<54func.h>
void handler(int signum){
    printf("signum=%d\n",signum);
    sleep(5);
}
int main(int argc,char *argv[]){
    //这样就没办法CTRL+c终止进程
    //接收到TRCL+c信号会去处理handler
    //再handler执行的过程中再次接受一次或多次中断信号，
    //只会缓存一次（位图），等handler执行完，再进入handler（只有一次）
    signal(SIGINT,handler); //signal是不会阻塞的
    while(1){
        sleep(1);
    }
    return 0;
}