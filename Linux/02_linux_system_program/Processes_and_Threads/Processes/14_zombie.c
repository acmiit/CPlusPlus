#include<54func.h>
int main(int argc,char*argv[]){
    if(fork()){
        printf("I am parent , pid=%d ,ppid= %d\n",getpid(),getppid());
        while(1){
            sleep(1);
        }
    }
    //子进程退出，但是主进程一直在运行，
    //子进程变为僵尸进程一直占用资源，不能复活
    //会影响计算机性能
    else{
        printf("I am child , pid=%d ,ppid= %d\n",getpid(),getppid());
        return 0;
    }
    return 0;
}