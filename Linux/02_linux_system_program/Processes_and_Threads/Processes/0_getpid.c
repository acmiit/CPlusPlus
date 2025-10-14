#include<54func.h>
// ps -elf 查看进程信息
int main(int argc,char*argv[]){
    printf(" pid= %d , ppid=%d\n",getpid(),getppid());
    return 0;
}