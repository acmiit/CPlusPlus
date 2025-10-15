#include<54func.h>
#define NUM 100
int main(int argc,char *argv[]){
    int shmid=shmget(0x1234,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmget,-1,"shmget");
    printf("shmid = %d\n",shmid);
    int *p=(int  *)shmat(shmid,NULL,0);
    if(fork()){
        for(int i=0;i<NUM;i++){
            ++*p;
        }
        wait(NULL);
        printf("*p=%d\n",*p);
    }else{
        for(int i=0;i<NUM;i++){
            ++*p;
        }
    }
    return 0;
}