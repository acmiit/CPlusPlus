#include<54func.h>
pthread_mutex_t mutex;
void *threadFun(void *arg){
    pthread_mutex_lock(&mutex);
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    //检错锁这能解决第三种死锁，（14_errorcheck.c）,没办法解决第二种死锁（本代码）
    pthread_mutexattr_t mutexattr; //定义一个锁属性类型
    pthread_mutexattr_init(&mutexattr); //初始化锁属性
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK); //设置锁属性为检错锁
    pthread_mutex_init(&mutex,&mutexattr); //mutex 就是一个检错类型的互斥锁

    pthread_t tid;
    pthread_create(&tid,NULL,threadFun,NULL);
    sleep(1);
    int ret;
    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"lock");
    printf("I got lock!\n");
    pthread_mutex_unlock(&mutex);
    return 0;
}