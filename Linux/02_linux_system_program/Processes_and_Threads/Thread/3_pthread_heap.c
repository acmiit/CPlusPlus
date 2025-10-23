#include<54func.h>
void *threadFunc(void *arg){
    int *p=(int *)arg;
    printf("child *p = %d\n",(*p)++);
    return NULL;
}
//堆内存错误
void func(){
    int *p=(int *)malloc(sizeof(int));
    *p=1000; 
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,p);
}
int main(int argc,char *argv[]){   

    sleep(1);
    return 0;
}