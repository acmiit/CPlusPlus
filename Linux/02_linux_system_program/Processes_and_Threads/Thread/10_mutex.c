#include<54func.h>
#define NUM 10000000
typedef struct shareRes_s{
    int val;
    pthread_mutex_t mutex;
}shareRes_t;
void *threadFun(void *arg){
    shareRes_t *pshareRes = (shareRes_t *)arg;
    for(int i=0;i<NUM;i++){
        pthread_mutex_lock(&pshareRes->mutex);
        ++(*pshareRes).val;
        pthread_mutex_unlock(&pshareRes->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    shareRes_t shareRes;
    shareRes.val=0;
    struct timeval begTime,endTime;
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_t tid;
    gettimeofday(&begTime,NULL);
    pthread_create(&tid,NULL,threadFun,&shareRes);
    for(int i=0;i<NUM;i++){
        pthread_mutex_lock(&shareRes.mutex);
        ++shareRes.val;
        pthread_mutex_unlock(&shareRes.mutex);
    }
    pthread_join(tid,NULL);
    gettimeofday(&endTime,NULL);
    printf("val = %d , total time = %ld us\n",shareRes.val,
    (endTime.tv_sec-begTime.tv_sec)*1000*1000+endTime.tv_usec-begTime.tv_usec);
    return 0;
}