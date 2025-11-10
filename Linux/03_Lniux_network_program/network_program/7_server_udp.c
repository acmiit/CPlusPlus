#include<54func.h>
int main(int argc,char *argv[]){
    // ./7_server_udp 172.22.195.222 1234
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));    
    //第一次必须是客户端向服务端发消息
    struct sockaddr_in clientaddr;
    socklen_t socklen=sizeof(clientaddr);
    char buf[4096]={0};
    recvfrom(sockfd,buf,4096,0,
    (struct sockaddr *)&clientaddr,&socklen);
    printf("buf = %s,ip =%s,port =%d\n",buf,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            memset(buf,0,4096);
            ssize_t sret = recvfrom(sockfd,buf,4096,0,NULL,NULL);
            if(sret == 0){
                break;
            }
            printf("sret = %ld,buf=%s\n",sret,buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,4096);
            ssize_t sret = read(STDIN_FILENO,buf,4096);
            if(sret==0){
                sendto(sockfd,buf,0,0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
                break;
            }
            sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
        }
    }
    return 0;
}