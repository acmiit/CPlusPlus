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
    int netfd =accept(sockfd,NULL,NULL);
    fd_set rdset; 
    char buf[4096]={0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(netfd,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        select(netfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(netfd,buf,strlen(buf),0);
        }
        if(FD_ISSET(netfd,&rdset)){
            memset(buf,0,sizeof(buf));
            ssize_t sret=recv(netfd,buf,sizeof(buf),0);
            if(sret ==0)
            {
                break;
            }
            printf("buf=%s\n",buf);
        }
    }
    return 0;
}