#include<54func.h>
void *threadFun(void *arg){
    time_t now=time(NULL);
    char *p;
    p=ctime(&now);
    printf("before p = %s\n",p);
    sleep(5);
    printf("after p = %s\n",p);
    pthread_exit(NULL);
}
int main(int argc,char *argv[]){
    pthread_t tid;
    pthread_create(&tid,NULL,threadFun,NULL);
    sleep(2);
    time_t now=time(NULL);
    char *p;
    p=ctime(&now);
    printf("main p = %s\n",p);
    pthread_join(tid,NULL);
    return 0;
}