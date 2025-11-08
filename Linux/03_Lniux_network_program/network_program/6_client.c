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

    send(sockfd,"hello",5,0);
    char buf[4096]={0};
    ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
    printf("sret = %ld , buf = %s\n",sret ,buf);
    return 0;
}