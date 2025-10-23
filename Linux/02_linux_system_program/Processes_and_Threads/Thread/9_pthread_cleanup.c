#include<54func.h>
void freep1(void *arg){
    printf("free p1\n");
    free((int *)arg);
}
void freep2(void *arg){
    printf("free p2\n");
    free((int *)arg);
}
void closefd3(void *arg){
    printf("close fd3\n");
    int *pfd=(int *)arg;
    close(&pfd);
}
void *threadFunc(void *arg){
    int *p1=(int *)malloc(4);
    int *p2=(int *)malloc(4);
    int fd3 = open("file1",O_RDONLY);
   //push 和 pop必须成对出现
   //不然会触发编译错误 
    //压栈
    pthread_cleanup_push(freep1,p1);
    printf("-----------------\n");
    pthread_exit(NULL);
    pthread_cleanup_push(freep2,p2);
    pthread_cleanup_push(closefd3,fd3);

    //弹栈
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);


}
int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    pthread_join(tid,NULL); 
    return 0;
}