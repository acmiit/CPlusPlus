#include<54func.h>
void *threadFun(void *arg){
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    //分离属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_t tid;
    pthread_create(&tid,&attr,threadFun,NULL);
    int ret =pthread_join(tid,NULL);
    THREAD_ERROR_CHECK(ret , "pthread join");
    return 0;
}