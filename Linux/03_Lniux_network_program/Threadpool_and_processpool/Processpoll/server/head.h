#include<54func.h>
enum{
    FREE,
    BUSY
};
typedef struct workerdata_s{
    pid_t pid;
    int status;
    int pipesockfd; //父进程和子进程通信用的socketpair的fd
}workerdata_t;

int makeWorker(int workerNum,workerdata_t *workerArr);
int tcpInit(const char *ip,char *port,int *psockfd);
int epollAdd(int epfd,int fd);
int epollDel(int epfd,int fd);
int sendfd(int sockfd,int fdtosend);
int recvfd(int sockfd,int *pfdtorecv);