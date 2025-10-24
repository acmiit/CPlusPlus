#include<54func.h>
int main(int argc,char *argv[]){
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr; //定义一个锁属性类型
    pthread_mutexattr_init(&mutexattr); //初始化锁属性
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK); //设置锁属性为检错锁
    pthread_mutex_init(&mutex,&mutexattr); //mutex 就是一个检错类型的互斥锁
    int ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"first lock");
    printf("first lock!\n");
    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"second lock");
    printf("second lock!\n");
    return 0;
}