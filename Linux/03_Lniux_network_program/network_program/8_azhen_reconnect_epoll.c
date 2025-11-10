#include<54func.h>
int main(int argc,char * argv[]){
    // ./6_server 172.22.195.222 1234
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int reuse=1; //允许重用
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    ERROR_CHECK(ret, -1,"setsockopt");
    ret = bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret ,-1,"bind");
    listen(sockfd,50);
    int netfd =-1;

    int epfd=epoll_create(1); 
    //设置监听
    struct epoll_event events;
    events.events=EPOLLIN;
    events.data.fd=sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&events);
    char buf[4096]={0};
    while(1){
        struct epoll_event readySet[1024];
        int readyNum=epoll_wait(epfd,readySet,1024,-1);
        for(int i=0;i<readyNum;i++){
            if(readySet[i].data.fd==sockfd){
                netfd=accept(sockfd,NULL,NULL);
                printf("aqiang is connectd!,netfd=%d\n",netfd);
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                events.events=EPOLLIN;
                events.data.fd=STDIN_FILENO;
                epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&events);
                events.events=EPOLLIN;
                events.data.fd=netfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,netfd,&events);
            }else if(netfd !=-1 &&readySet[i].data.fd==netfd){
                memset(buf,0,sizeof(buf));
                ssize_t sret= recv(netfd,buf,sizeof(buf),0);
                if(sret ==0)
                {
                    printf("aqiang has dead!\n");
                    epoll_ctl(epfd,EPOLL_CTL_DEL,netfd,NULL);
                    epoll_ctl(epfd,EPOLL_CTL_DEL,STDIN_FILENO,NULL);
                    events.events=EPOLLIN;
                    events.data.fd=sockfd;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&events);
                    close(netfd);
                    netfd=-1;
                    break;
                }
                printf("buf = %s\n",buf);
            }else if(netfd !=-1 && readySet[i].data.fd==STDIN_FILENO){
                memset(buf,0,sizeof(buf));
                ssize_t sret =read(STDIN_FILENO,buf,sizeof(buf));
                if(sret ==0)
                {
                    printf("kick aqiang!\n");
                    epoll_ctl(epfd,EPOLL_CTL_DEL,netfd,NULL);
                    epoll_ctl(epfd,EPOLL_CTL_DEL,STDIN_FILENO,NULL);
                    events.events=EPOLLIN;
                    events.data.fd=sockfd;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&events);
                    close(netfd);
                    netfd=-1;
                    break;
                }
                send(netfd,buf,sret,0);
            }
        }
    };
    return 0;
}