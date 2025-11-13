#include"head.h"
int makeWorker(int workerNum,workerdata_t *workerArr){
    for(int i=0;i<workerNum;i++){
        pid_t pid=fork();
        if(pid==0){
            while(1){
                sleep(1);
            }
        }
        workerArr[i].status=FREE;
        workerArr[i].pid=pid;
    }
}