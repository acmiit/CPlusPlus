#include"head.h"
int exitPipe[2];
void handler(int signum){
    printf("signum = %d\n",signum);
    write(exitPipe[1],"1",1);
}
int main(int argc,char *argv[]){
    // ,.server 172.22.195.222 1234 3
    ARGS_CHECK(argc,4);
    int workerNum=atoi(argv[3]);
    workerdata_t * workerArr=(workerdata_t *)calloc(workerNum,sizeof(workerdata_t));
    //创建了子进程，获取每个子进程的状态
    makeWorker(workerNum,workerArr);
    //创建一个自己和自己通信的管道
    pipe(exitPipe);
    //注册10号信号
    signal(SIGUSR1,handler);

    int sockfd;
    //初始化tcp服务端
    tcpInit(argv[1],argv[2],&sockfd);
    //初始化epoll
    int epfd=epoll_create(1);
    for(int i=0;i<workerNum;i++){
        epollAdd(epfd,workerArr[i].pipesockfd);
    }
    epollAdd(epfd,sockfd);
    epollAdd(epfd,exitPipe[0]);
    while(1){
        struct epoll_event readySet[1024];
        int readyNum=epoll_wait(epfd,readySet,1024,-1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==sockfd){
                int netfd=accept(sockfd,NULL,NULL);
                printf("1 client is connected!\n");
                //顺序查找空闲的子进程
                for(int j=0;j<workerNum;j++){
                    if(workerArr[j].status==FREE){
                        sendfd(workerArr[j].pipesockfd,netfd);
                        workerArr[j].status=BUSY;
                        break;
                    }
                }
                //没有空闲的子进程的就拒绝访问
                close(netfd);
            }else if(readySet[i].data.fd==exitPipe[0]){
                //进程池要退出了
                for(int j=0;j<workerNum;j++){
                    kill(workerArr[j].pid,SIGKILL);
                    printf("Kill 1 worker!\n");
                }
                for(int j=0;j<workerNum;j++){
                    wait(NULL);
                }
                printf("All workers are killed!\n");
                exit(0);
            }else{
                //某个子进程完成任务了
                int pipesockfd=readySet[i].data.fd;
                for(int j=0;j<workerNum;j++){
                    if(workerArr[i].pipesockfd == pipesockfd){
                        pid_t pid;
                        recv(pipesockfd,&pid,sizeof(pid),0);
                        workerArr[i].status=FREE;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}