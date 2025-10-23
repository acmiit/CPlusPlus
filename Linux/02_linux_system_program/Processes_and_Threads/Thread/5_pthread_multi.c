#include<54func.h>
void *threadFunc(void *arg){
    long i=(long)arg;
    printf("child i = %ld\n",i);
    return NULL;
}
int main(int argc,char *argv[]){   
    long i=1001; 
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,threadFunc,(void *)i);
    i++;
    pthread_create(&tid2,NULL,threadFunc,(void *)i);
    i++;
    pthread_create(&tid3,NULL,threadFunc,(void *)i);
    sleep(1);
    // printf("parent i = %d\n",i);
    return 0;
}