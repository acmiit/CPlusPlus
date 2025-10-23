#include<54func.h>
void *threadFunc(void *arg){
    int * pfd=(int *)arg;
    sleep(1);
    lseek(*pfd,0,SEEK_SET); 
    char buf[1024]={0};
    read(*pfd,buf,sizeof(buf));
    printf("buf = %s\n",buf);

}
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd, -1 ,"open");

    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&fd);
    write(fd, "hello",5);
    sleep(2);
    return 0;
}