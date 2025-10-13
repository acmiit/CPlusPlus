#include<54func.h>
int main(int argc,char*argv[]){
    pid_t ret = fork();
    if(!ret){
        printf("I am parent , pid=%d ,ppid= %d\n",getpid(),getppid());
        sleep(1);
    }
    else{
        printf("I am child , pid=%d ,ppid= %d\n",getpid(),getppid());
    }
    return 0;
}