#include <54func.h>
int main(int argc, char *argv[])
{
    // ./5_aqiang 192.168.72.128 1234
    // 192.168.72.128:1234 
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");
     
    fd_set rdset;
    int epfd=epoll_create(1);
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
    events.events = EPOLLIN;
    events.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events);
    char buf[4096] = {0};
    int flag=0;
    while(1){
        struct epoll_event readySet[2];
        int readyNum = epoll_wait(epfd, readySet, 1024, -1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==STDIN_FILENO){
                memset(buf,0,sizeof(buf));
                ssize_t sret = read(STDIN_FILENO,buf,sizeof(buf));
                if(sret == 0){
                    printf("nishihehaoren!\n");
                    flag=1;
                    break;
                }
                send(sockfd,buf,strlen(buf),0);
            }else if(readySet[i].data.fd==sockfd){
                memset(buf,0,sizeof(buf));
                ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
                if(sret == 0){
                    printf("hehe\n");
                    flag=1;
                    break;
                }
                printf("buf=%s\n",buf);
            }
        }
        if(flag==1){
            break;
        }
    }
 
    return 0;
}