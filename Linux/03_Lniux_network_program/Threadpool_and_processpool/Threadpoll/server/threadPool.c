#include"threadPool.h"
#include"worker.h"
int threadPollInit(threadPool_t *pthreadPool,int workNum){
    tidArrInit(&pthreadPool->tidArr,workNum);
    taskQueueInit(&pthreadPool->taskQueue);
    pthread_mutex_init(&pthreadPool->mutex,NULL);
    pthread_cond_init(&pthreadPool->cond,NULL);
    pthreadPool->exitFlag=0;
    return 0;
}

int makeWorker(threadPool_t *pthreadPool){
    for(int i=0;i<pthreadPool->tidArr.workerNum;i++){
        pthread_create(&pthreadPool->tidArr.arr[i],NULL,threadFunc,pthreadPool);
    }
    return 0;
}