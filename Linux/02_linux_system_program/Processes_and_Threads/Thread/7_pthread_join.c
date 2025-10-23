#include<54func.h>
void * threadFunc(void *arg){
    // return NULL;
    pthread_exit((void *)123);
    printf("Can you see me!\n");
}
int main(){
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    void * retval;
    pthread_join(tid,&retval);
    printf("retval = %ld\n",(long)retval);
    return 0;
}