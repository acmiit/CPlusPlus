#include<54func.h>
#define NUM 10000000
int global=0;
void *threadFunc(void *arg){
    for(int i=0;i<NUM;i++){
        ++global;
    }
    printf("child add finish!\n");
}
int main(int argc,char *argv[]){
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    for(int i=0;i<NUM;i++){
        ++global;
    }
    printf("main add finish!\n");
    sleep(1);
    printf("global = %d\n",global);
    return 0;
}