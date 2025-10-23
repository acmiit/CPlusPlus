#include<54func.h>
void *routine(void *arg){
    printf("I am child thread!\n");
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);
    printf("I am parent thread!\n");
    sleep(1);
    return 0;
}
