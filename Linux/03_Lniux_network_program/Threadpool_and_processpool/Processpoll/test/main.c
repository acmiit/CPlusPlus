#include"head.h"
int main(int argc,char *argv[]){
    workerdata_t workers[3];
    makeWorker(3,workers);
    for(int i=0;i<3;i++){
        printf("pid=%d\n",workers[i].pid);
    }
    while(1){
        sleep(1);
    }
    return 0;
}