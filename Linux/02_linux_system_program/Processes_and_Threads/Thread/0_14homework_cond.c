#include<54func.h>
typedef struct shareRes_s {
    int flag;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shareRes_t;
void * threadFun(void *arg){
    shareRes_t * pshareRes = (shareRes_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    if(pshareRes->flag==0){
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pthread_mutex_unlock(&pshareRes->mutex);
    printf("Before B!\n");
    sleep(3);
    printf("After B!\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    shareRes_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex,NULL); 
    pthread_cond_init(&shareRes.cond,NULL);
    pthread_t tid;
    pthread_create(&tid,NULL,threadFun,&shareRes);
    pthread_mutex_unlock(&shareRes.mutex);
    printf("Before A!\n");
    sleep(3);
    printf("After A!\n");
    shareRes.flag=1;
    pthread_mutex_unlock(&shareRes.mutex);
    pthread_cond_signal(&shareRes.cond);
    pthread_join(tid,NULL);
    return 0;
}