#include<54func.h>
int main(int argc,char *argv[]){
    if(fork()){
        printf("I am parent, pid = %d,ppid=%d,pgid = %d, pgid of ppid = %d\n"
            ,getpid(),getppid(),getpgid(0),getpgid(getppid()));
        wait(NULL);
    }else{
        printf(" Before I am child, pid = %d,ppid=%d,pgid = %d, pgid of ppid = %d\n"
            ,getpid(),getppid(),getpgid(0),getpgid(getppid()));
        //吧gpid设置为pid，组长不能修改
        setpgid(0,0);

        printf(" Before I am child, pid = %d,ppid=%d,pgid = %d, pgid of ppid = %d\n"
            ,getpid(),getppid(),getpgid(0),getpgid(getppid()));
    }
    return 0;
}