#include<54func.h>
typedef struct shareRes_s{
    int flag;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;
void* threadFun(void *arg){
    shareRes_t *pshareRes =(shareRes_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag!=1){
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pthread_mutex_unlock(&pshareRes->mutex);
    sleep(3);
    printf("B\n");
    pthread_mutex_lock(&pshareRes->mutex);
    pshareRes->flag=2;
    pthread_cond_signal(&pshareRes->cond);
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    pthread_t tid;
    shareRes_t shareRes;
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_cond_init(&shareRes.cond,NULL);
    shareRes.flag=0;
    pthread_create(&tid,NULL,threadFun,&shareRes);
    printf("A\n");
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.flag=1;
    pthread_cond_signal(&shareRes.cond);
    pthread_mutex_unlock(&shareRes.mutex);
    while(shareRes.flag!=2){
        pthread_cond_wait(&shareRes.cond,&shareRes.mutex);
    }
    pthread_mutex_unlock(&shareRes.mutex);
    sleep(3);
    printf("C\n");
    pthread_join(tid,NULL);
    return 0;
}