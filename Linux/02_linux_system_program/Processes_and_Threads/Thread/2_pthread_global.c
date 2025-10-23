#include<54func.h>
int global = 1000;
void *threadFunc(void *arg){
    printf("child global = %d\n",global++);
}
int main(int argc,char *argv[]){    
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    sleep(1);
    printf("main global = %d\n",global);
    return 0;
}