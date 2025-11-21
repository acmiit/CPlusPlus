#include<54func.h>
//1.0   消息没有边界 火车头：给消息增加边界，解决“粘包”问题
// int recvFile(int sockfd){
//     char filename[1024]={0};
//     recv(sockfd,filename,sizeof(filename),0);
//     int fd=open(filename,O_CREAT|O_RDWR,0666);
//     char buf[1024]={0};
//     ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
//     write(fd,buf,sret);
//     return 0;
// }

//2.0
typedef struct train_s{
    int length;//火车头
    char data[1024];
}train_t;

int recvn(int sockfd,void *buf,long total){
    char *p=(char *)buf;
    long cursize=0;
    while(cursize<total){
        ssize_t sret = recv(sockfd,p+cursize,total-cursize,0);
        if(sret==0){
            return 1;
        }
        cursize+=sret;
    }
    return 0;
}
// int recvFile(int sockfd){
//     char filename[1024]={0};
//     train_t train;
//     recv(sockfd,&train.length,sizeof(train.length),0);
//     recv(sockfd,train.data,train.length,0);
//     memcpy(filename,train.data,train.length);

//     int fd=open(filename,O_CREAT|O_RDWR,0666);
//     recv(sockfd,&train.length,sizeof(train.length),0);
//     recv(sockfd,train.data,train.length,0);
//     write(fd,train.data,train.length);
//     close(fd);
//     return 0;
// }
//3.0
// int recvFile(int sockfd){
//     char filename[1024]={0};
//     train_t train;
//     recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//     recv(sockfd,train.data,train.length,MSG_WAITALL);
//     memcpy(filename,train.data,train.length);
//     int fd=open(filename,O_CREAT|O_RDWR|O_TRUNC,0666);
//     while(1){
//         recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//         if(train.length!=1024){
//             printf("train.length = %d\n",train.length);
//         }
//         if(train.length==0){
//             break;
//         }
//         recv(sockfd,train.data,train.length,MSG_WAITALL);
//         write(fd,train.data,train.length);
//     }

//     close(fd);
//     return 0;
// }
//4.0
// int recvFile(int sockfd){
//     char filename[1024]={0};
//     train_t train;
//     // recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//     // recv(sockfd,train.data,train.length,MSG_WAITALL);
//     recvn(sockfd,&train.length,sizeof(train.length));
//     recvn(sockfd,train.data,train.length);
//     memcpy(filename,train.data,train.length);

//     off_t filesize;
//     // recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//     // recv(sockfd,train.data,train.length,MSG_WAITALL);
//     recvn(sockfd,&train.length,sizeof(train.length));
//     recvn(sockfd,train.data,train.length);
//     memcpy(&filesize,train.data,train.length);
//     printf("filesize = %ld\n",filesize);
//     int fd=open(filename,O_CREAT|O_RDWR|O_TRUNC,0666);

//     off_t cursize=0;
//     off_t lastsize = 0;
//     off_t slice=filesize/10000;
//     while(1){
//         // recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//         recvn(sockfd,&train.length,sizeof(train.length));
//         if(train.length!=1024){
//             printf("train.length = %d\n",train.length);
//         }
//         if(train.length==0){
//             break;
//         }
//         cursize +=train.length;
//         // recv(sockfd,train.data,train.length,MSG_WAITALL);
//         recvn(sockfd,train.data,train.length);
//         write(fd,train.data,train.length);
//         if(cursize-lastsize>slice){
//             printf("%5.2lf%%\r",cursize*100.0/filesize);
//             fflush(stdout);
//             lastsize=cursize;
//         }
//     }
//     printf("100.00%%\n");
//     close(fd);
//     return 0;
// }
//5.0
int recvFile(int sockfd){
    char filename[1024]={0};
    train_t train;
    // recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
    // recv(sockfd,train.data,train.length,MSG_WAITALL);
    recvn(sockfd,&train.length,sizeof(train.length));
    recvn(sockfd,train.data,train.length);
    memcpy(filename,train.data,train.length);

    off_t filesize;
    // recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
    // recv(sockfd,train.data,train.length,MSG_WAITALL);
    recvn(sockfd,&train.length,sizeof(train.length));
    recvn(sockfd,train.data,train.length);
    memcpy(&filesize,train.data,train.length);
    printf("filesize = %ld\n",filesize);
    int fd=open(filename,O_CREAT|O_RDWR|O_TRUNC,0666);
    ftruncate(fd,filesize); //先修改文件大小
    char *p=(char *)mmap(NULL,filesize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap");
    recvn(sockfd,p,filesize);
    munmap(p,filesize);
    close(fd);
    return 0;
}

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret ,-1,"connect")
    recvFile(sockfd);
    return 0;
}