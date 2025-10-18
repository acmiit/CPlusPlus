#include<54func.h>
void handler(int signum){
    printf("Before signum=%d\n",signum);
    sleep(5);
    printf("After signum=%d\n",signum);
}
int main(int argc,char *argv[]){
    //这样就没办法CTRL+c终止进程
    //接收到TRCL+c信号会去处理handler
    //再handler执行的过程中再次接受一次或多次中断信号，
    //同种信号只会记录一次（位图），等handler执行完，再进入handler（只有一次）
    //对于不同的信号，2号信号handler接受3号信号会进出handler
    //mask pedding 
    signal(SIGINT,handler); //signal是不会阻塞的
    signal(SIGQUIT,handler); //signal是不会阻塞的
    while(1){
        sleep(1);
    }
    return 0;
}