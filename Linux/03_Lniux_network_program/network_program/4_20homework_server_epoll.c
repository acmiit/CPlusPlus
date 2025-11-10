#include<54func.h>
typedef struct Conn_s{
    int isAlive;
    int netfd;
    time_t lastActive;
}Conn_t;
 
//实现一个聊天室并10秒不发言开始踢人
int main(int argc,char*argv[])
{
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));
 
    int reuse = -1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");
    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");
    listen(sockfd, 50);
 
    int epfd = epoll_create(1);
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
 
    Conn_t conn[1024];
    for(int i = 0; i < 1024; i++){
        conn[i].isAlive = 0;
    }
 
    int fdToidx[1024];
    for(int i = 0; i < 1024; i++){
        fdToidx[i] = -1;
    }
 
    int curidx = 0;
 
    char buf[4096];
    time_t now;
 
    while(1){
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epfd, readySet, 1024, 1000);
        now = time(NULL);
        printf("now = %s\n", ctime(&now));
 
        //遍历就绪集合
        for(int i = 0; i < readyNum; i++){
            if(readySet[i].data.fd == sockfd){//sockfd 就绪说明有新的链接来到，
                int netfd = accept(sockfd, NULL, NULL);//accept新的链接并把netfd加入监听
                printf("id = %d, netfd = %d\n", curidx, netfd);
                conn[curidx].isAlive = 1;
                conn[curidx].netfd = netfd;
                conn[curidx].lastActive = time(NULL);
                fdToidx[netfd] = curidx;
 
                events.events = EPOLLIN;
                events.data.fd = netfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &events);
                ++curidx;
            }
            else {//否则就是netfd就绪即有客户端说话，此时服务端完成接收与转发
                int netfd = readySet[i].data.fd;
                memset(buf, 0 ,sizeof(buf));
                ssize_t sret = recv(netfd, buf, sizeof(buf), 0);//接收
                if(sret == 0){//断开链接的情况，把该netfd置为-1，链接isAlive置为0,关闭netfd
                    printf("1 client is closed!\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL,netfd, NULL);
                    int idx = fdToidx[netfd];
                    conn[idx].isAlive = 0;
                    fdToidx[netfd] = -1;
                    close(netfd);
                    continue;
 
                }
                int idx = fdToidx[netfd]; //通过netfd找到当前的下标idx，再定位到数据结构
                conn[idx].lastActive = time(NULL);//记录这个数据结构对象的最后活跃时间
                for(int j = 0; j < curidx; ++j){ //遍历找到未断开链接的客户端向他们发送信息
                    if(conn[j].isAlive == 1 && conn[j].netfd != netfd){
                        send(conn[j].netfd, buf, strlen(buf), 0);
                    }
                }
            }
        }
 
        for(int i = 0; i < curidx; ++i){//检查超时的客户端并踢出去
            if(conn[i].isAlive == 1 && now - conn[i].lastActive > 10){
                epoll_ctl(epfd, EPOLL_CTL_DEL, conn[i].netfd, NULL);
                close(conn[i].netfd);
                conn[i].isAlive = 0;
                fdToidx[conn[i].netfd] = -1;
            }
        }
    }
 
    return 0;
}