#include<54func.h>
int main(int argc,char argv[]){
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(1234);
    char ip[]="172.22.195.222";
    inet_aton(ip,&addr.sin_addr);
    printf("ip=%x\n",addr.sin_addr.s_addr);
    return 0;
}