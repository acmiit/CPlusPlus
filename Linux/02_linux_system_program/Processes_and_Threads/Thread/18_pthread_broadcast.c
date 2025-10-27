#include<54func.h>
typedef struct shareRes_s{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int flag;
}shareRes_t;
void * classmate1(void *arg){
    shareRes_t * pshareRes=(shareRes_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag!=1){
        printf("1 is not ready!\n");
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pshareRes->flag=0;
    pthread_mutex_unlock(&pshareRes->mutex);
    printf("I got 1\n");
    pthread_exit(NULL);
}
void * classmate2(void *arg){
    shareRes_t * pshareRes=(shareRes_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag!=2){
        printf("2 is not ready!\n");
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pshareRes->flag=0;
    pthread_mutex_unlock(&pshareRes->mutex);
    printf("I got 2\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    shareRes_t shareRes;
    shareRes.flag=0;
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_cond_init(&shareRes.cond,NULL);
    pthread_t tid1 ,tid2;
    pthread_create(&tid1,NULL,classmate1,&shareRes);
    pthread_create(&tid2,NULL,classmate2,&shareRes);
    while(1){
        int i;
        scanf("%d",&i);
        printf("I producer %d\n",i);
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.flag=i;
        pthread_cond_broadcast(&shareRes.cond);
        pthread_mutex_unlock(&shareRes.mutex);
    }
    return 0;
}