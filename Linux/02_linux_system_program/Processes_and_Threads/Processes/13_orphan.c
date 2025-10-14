#include<54func.h>
int main(int argc,char*argv[]){
    if(fork()){
        printf("I am parent , pid=%d ,ppid= %d\n",getpid(),getppid());
        return 0;
    }
    else{
        printf("I am child , pid=%d ,ppid= %d\n",getpid(),getppid());
        while(1){
            sleep(1);
        }
    }
    return 0;
}