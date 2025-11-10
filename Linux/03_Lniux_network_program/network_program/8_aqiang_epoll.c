#include<54func.h>
int main(int argc,char * argv[]){
    // ./6_client 172.22.195.222 1234
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret ,-1,"connect");

    int epfd=epoll_create(1);
    char buf[4096]={0};
    //设置监听
    struct epoll_event events;
    events.events=EPOLLIN;
    events.data.fd=STDIN_FILENO;
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&events);
    events.events=EPOLLIN;
    events.data.fd=sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&events);
    int flag=0;
    while(1){
        struct epoll_event readySet[2];
        int readyNum=epoll_wait(epfd,readySet,2,-1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==STDIN_FILENO){
                memset(buf,0,sizeof(buf));
                ssize_t sret =read(STDIN_FILENO,buf,sizeof(buf));
                if(sret ==0)
                {
                    break;
                }
                send(sockfd,buf,sret,0);
            }else if(readySet[i].data.fd==sockfd){
                memset(buf,0,sizeof(buf));
                ssize_t sret= recv(sockfd,buf,sizeof(buf),0);
                if(sret ==0)
                {
                    flag=1;
                    break;
                }
                printf("buf = %s\n",buf);
            }
        }
        if(flag=1){
            break;
        }
    }
    return 0;
}