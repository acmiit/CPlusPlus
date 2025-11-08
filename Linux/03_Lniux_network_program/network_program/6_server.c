#include<54func.h>
int main(int argc,char * argv[]){
    // ./6_server 172.22.195.222 1234
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret = bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret ,-1,"bind");
    listen(sockfd,50);
    //sockfd是监听socket的文件描述符
    struct sockaddr_in clientAddr;
    socklen_t socklen=sizeof(clientAddr);
    //socklen 必须赋值s
    int netfd =accept(sockfd,(struct sockaddr *)&clientAddr,&socklen);
    //netfd 是通信socket的文件描述符
    printf("client ip= %s,port = %d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    
    char buf[4096]={0};
    // ssize_t sret =recv(netfd,buf,sizeof(buf),0);
    ssize_t sret =read(netfd,buf,sizeof(buf));
    printf("sret = %ld , buf = %s\n",sret ,buf);
    send(netfd,"nihao",5,0);
    return 0;
}