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

    fd_set monitorSet;
    fd_set readySet;
    FD_ZERO(&monitorSet);
    FD_SET(sockfd,&monitorSet);
    char buf[4096]={0};
    int netfd=-1;
    while(1){
        memcpy(&readySet,&monitorSet,sizeof(monitorSet));
        select(20,&readySet,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&readySet)){
            netfd=accept(sockfd,NULL,NULL);
            printf("aqiang is connected!\n");
            FD_CLR(sockfd,&monitorSet);
            FD_SET(STDIN_FILENO,&monitorSet);
            FD_SET(netfd,&monitorSet);
        }
        if(FD_ISSET(netfd,&readySet)){
            memset(buf,0,sizeof(buf));
            ssize_t sret=recv(netfd,buf,sizeof(buf),0);
            if(sret ==0)
            {
                //阿强断开连接了
                FD_SET(sockfd,&monitorSet);
                FD_CLR(STDIN_FILENO,&monitorSet);
                FD_CLR(netfd,&monitorSet);
                close(netfd);
                netfd=-1;
                printf("wohuihaohaode!\n");
                continue;
            }
            printf("buf=%s\n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&readySet)){
            memset(buf,0,sizeof(buf));
            ssize_t sret=read(STDIN_FILENO,buf,sizeof(buf));
            if(sret == 0){ //按下了CTRL+D 踢人
                FD_SET(sockfd,&monitorSet);
                FD_CLR(STDIN_FILENO,&monitorSet);
                FD_CLR(netfd,&monitorSet);
                close(netfd);
                netfd=-1;
                printf("nishigehaoren!\n");
                continue;
            }
            send(netfd,buf,strlen(buf),0);
        }

    }
    return 0;
}