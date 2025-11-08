#include<54func.h>
typedef struct node_s{
    int id;
    struct node_s * next;
}node_t;
typedef struct Queue_s{
    int Queuesize;
    node_t *pFront;
    node_t *pRear;
}Queue_t;
typedef struct shareRes_s{
    Queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;
int enQueue(Queue_t *pQueue,int data){
    node_t *pNew=(node_t *)malloc(sizeof(node_t));
    pNew->id=data;
    pNew->next = NULL;
    if(pQueue->Queuesize==0){
        pQueue->pFront=pNew;
        pQueue->pRear=pNew;
    }else{
        pQueue->pRear->next=pNew;
        pQueue->pRear=pNew;
    }
    ++pQueue->Queuesize;
    return 0;
}
int deQueue(Queue_t *pQueue){
    node_t *pCur=pQueue->pFront;
    int data=pCur->id;
    pQueue->pFront=pCur->next;
    if(pQueue->Queuesize==1){
        pQueue->pRear=NULL;
    }
    free(pCur);
    --pQueue->Queuesize;
    return data; 
}
int visitQueue(Queue_t *pQueue){
    node_t *pCur=pQueue->pFront;
    while(pCur){
        printf("%d ",pCur->id);
        pCur=pCur->next;
    }
    printf("\n");
    return 0;
}
void *producer(void *arg){
    shareRes_t *pshareRes = (shareRes_t *)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->queue.Queuesize>=10){
            pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
        }
        int data = rand()%1000;
        printf("producer product %d\n",data);
        enQueue(&pshareRes->queue,data);
        visitQueue(&pshareRes->queue);
        pthread_cond_broadcast(&pshareRes->cond);
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(3);
    }

}
void *comsumer(void *arg){
    shareRes_t *pshareRes = (shareRes_t *)arg;
    sleep(5);
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->queue.Queuesize<=0){
            pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
        }
        int data=deQueue(&pshareRes->queue);
        printf("comsumer spend %d\n",data);
        visitQueue(&pshareRes->queue);
        pthread_cond_broadcast(&pshareRes->cond);
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }

}
int main(int argc, char *argv[])
{

   shareRes_t shareRes;
   memset(&shareRes.queue,0,sizeof(shareRes.queue));
   pthread_mutex_init(&shareRes.mutex,NULL);
   pthread_cond_init(&shareRes.cond,NULL);

   for(int i=0;i<8;i++){
    int id=rand()%1000;
    enQueue(&shareRes.queue,id);
   }
   pthread_t tid1,tid2,tid3,tid4,tid5;
   pthread_create(&tid1,NULL,producer,&shareRes);
   pthread_create(&tid2,NULL,producer,&shareRes);
   pthread_create(&tid3,NULL,producer,&shareRes);
   pthread_create(&tid4,NULL,comsumer,&shareRes);
   pthread_create(&tid5,NULL,comsumer,&shareRes);

   pthread_join(tid1,NULL);
   pthread_join(tid2,NULL);
   pthread_join(tid3,NULL);
   pthread_join(tid4,NULL);
   pthread_join(tid5,NULL);
   return 0;
}