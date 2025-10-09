#include<54func.h>
int main(int argc,char* argv[]){
    // ./0_azhen_select 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdw = open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open write");
    int fdr = open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open read");
    printf("azhen is connected!\n");
    char buf[4096];
    fd_set rdset;
    time_t curTime;
    time_t lastActive=time(NULL);
    while(1){
        //select之前设置监听
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        struct timeval timeout;
        timeout.tv_sec=1;
        timeout.tv_usec=0;
        ssize_t ret = select(fdr+1,&rdset,NULL,NULL,&timeout);
        curTime=time(NULL);
        printf("curTime=%s\n",ctime(&curTime));
        //select返回之后，说明fdr or stdin就绪了 rdset现在是就绪集合
        if(FD_ISSET(fdr,&rdset)){
            lastActive=time(NULL);
            memset(buf,0,sizeof(buf));
            ssize_t ret = read(fdr,buf,sizeof(buf));
            if(ret == 0){
                printf("Hehe\n");
                break;
            }
            printf("buf=%s\n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            ssize_t ret =read(STDERR_FILENO,buf,sizeof(buf));
            if(ret == 0){
                write(fdw,"nishigehaoren\n",13);
                break;
            }
            write(fdw,buf,strlen(buf));
        }
        if(curTime-lastActive>=10){
            printf("byebye!\n");
            break;
        }
    }
    return 0;
}