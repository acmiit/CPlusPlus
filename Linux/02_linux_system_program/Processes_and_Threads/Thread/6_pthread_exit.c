#include<54func.h>
void * threadFunc(void *arg){
    // return NULL;
    pthread_exit(NULL);
    printf("Can you see me!\n");
}
int main(){
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}