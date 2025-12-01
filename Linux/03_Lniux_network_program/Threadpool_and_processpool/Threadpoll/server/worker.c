#include"worker.h"
#include"threadPool.h"
#include "taskQueue.h"
int tidArrInit(tidArr_t *ptidArr,int workNum){
    //申请内存 存储每个子线程的tid
    ptidArr->arr=(pthread_t *)calloc(workNum,sizeof(pthread_t));
    ptidArr->workerNum=workNum;
    return 0;
}
void unlock(void *arg){
    threadPool_t *pthreadPool=(threadPool_t *)arg;
    pthread_mutex_unlock(&pthreadPool->mutex);
    printf("unlock");
}

void *threadFunc(void *arg){
    threadPool_t *pthreadPool = (threadPool_t *)arg;
    int netfd;
    while(1){
        pthread_mutex_lock(&pthreadPool->mutex);
        // pthread_cleanup_push(unlock,pthreadPool);

        while(pthreadPool->exitFlag==0 && pthreadPool->taskQueue.queueSize<=0){
            pthread_cond_wait(&pthreadPool->cond,&pthreadPool->mutex);
        }
        if(pthreadPool->exitFlag ==1){
            printf("I am child,I am going to exit!\n");
            pthread_mutex_unlock(&pthreadPool->mutex);
            pthread_exit(NULL);
        }
        netfd =pthreadPool->taskQueue.pFront->netfd;
        printf("I am worker,I got a netfd = %d\n",netfd);
        deQueue(&pthreadPool->taskQueue);
        pthread_mutex_unlock(&pthreadPool->mutex);
        // pthread_cleanup_pop(1);
        //执行业务
        transFile(netfd);
        close(netfd);
    }
}