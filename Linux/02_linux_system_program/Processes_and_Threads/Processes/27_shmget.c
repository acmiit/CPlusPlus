#include<54func.h>
int main(int argc,char *argv[]){
    //IPC_CREAT,不存在key为0x1234的共享内存就创建大小为4096B大小的共享内存

    int shmid=shmget(0x1234,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmget,-1,"shmget");
    printf("shmid = %d\n",shmid);
    return 0;
}