#include<54func.h>
typedef struct Conn_s{
    int isConnected; //0表示未连接 1表示已连接
    int netfd; 
    time_t lastActive; //最后发消息时间
}Conn_t;
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
    Conn_t client[1024];
    for(int i=0;i<1024;i++){
        client[i].isConnected=0;
    }
    int curidex=0;
    int fdToidx[1024];
    for(int i=0;i<1024;i++){
        fdToidx[i]=-1;
    }
    fd_set monitorSet;
    fd_set readySet;
    FD_ZERO(&monitorSet);
    FD_SET(sockfd,&monitorSet);
    char buf[4096]={0};
    time_t now;
    while(1){
        memcpy(&readySet,&monitorSet,sizeof(monitorSet));
        struct timeval timeout;
        timeout.tv_sec=1;
        timeout.tv_usec=0;
        select(1024,&readySet,NULL,NULL,&timeout);
        now=time(NULL);
        printf("now =%s\n",ctime(&now));
        if(FD_ISSET(sockfd,&readySet)){ //新来的客户端连接
            client[curidex].isConnected=1;
            client[curidex].netfd=accept(sockfd,NULL,NULL);
            client[curidex].lastActive=time(NULL);
            printf("i=%d,netfd=%d,now=%s\n",curidex,client[curidex].netfd,ctime(&client[curidex].lastActive));
            fdToidx[client[curidex].netfd]=curidex;
            FD_SET(client[curidex].netfd,&monitorSet);
            curidex++;
        }
        for(int i=0;i<curidex;i++){
            if(client[i].isConnected==1 && FD_ISSET(client[i].netfd,&readySet)){
                memset(buf,0,sizeof(buf));
                ssize_t sret = recv(client[i].netfd,buf,sizeof(buf),0);
                if(sret == 0){
                    FD_CLR(client[i].netfd,&monitorSet);
                    close(client[i].netfd);
                    fdToidx[client[i].netfd]=-1;
                    client->isConnected=0;
                    continue;
                }
                client[i].lastActive=time(NULL);
                printf("i=%d,netfd=%d,now=%s\n",curidex,client[i].netfd,ctime(&client[i].lastActive));
                for(int j=0;j<curidex;j++){
                    if(client[j].isConnected==1 && j!=i){
                        send(client[j].netfd,buf,strlen(buf),0);
                    }
                }
            }
            for(int i=0;i<curidex;i++){
                if(client[i].isConnected==1 &&now-client[i].lastActive>5){
                    FD_CLR(client[i].netfd,&monitorSet);
                    close(client[i].netfd);
                    fdToidx[client[i].netfd]=-1;
                    client->isConnected=0;
                }
            }
        }
    }
    return 0;
}