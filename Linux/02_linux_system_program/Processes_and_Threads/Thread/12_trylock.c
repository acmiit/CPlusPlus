#include<54func.h>
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int main(int argc,char *argv[]){
    int ret;
    ret = pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret,"first");
    printf("first lock!\n");
    ret =pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret,"second");
    printf("second lock!\n");
    return 0;
}