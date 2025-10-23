#include<54func.h>
void *threadFunc(void *arg){
    int *p=(int *)arg;
    printf("child p = %d\n",(*p)++);
    return NULL;
}
void func(){
    int i=1000; 
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&i);

}
int main(int argc,char *argv[]){   
    func();
    sleep(1);
    // printf("parent i = %d\n",i);
    return 0;
}