#include<54func.h>
int main(int argc,char *argv[]){
    // ./7_server_udp 172.22.195.222 1234
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
    //第一次必须是客户端向服务端发消息
    sendto(sockfd,"hello",5,0,
    (struct sockaddr *)&serveraddr,sizeof(serveraddr));
    char buf[4096]={0};
    recvfrom(sockfd,buf,4096,0,NULL,NULL);
    printf("buf = %s\n",buf);
   return 0;
} 