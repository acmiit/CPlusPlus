#include<54func.h>
int main (int argc,char *argv[]){
    // ./1_07homework file1 file2
    ARGS_CHECK(argc,3);
    int fd1=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd1,-1,"open1");
    int fd2=open(argv[2],O_RDONLY);
    ERROR_CHECK(fd2,-1,"open2");
    char buf1[1024];
    char buf2[1024];
    while(1){
        memset(buf1,0,sizeof(buf1));
        memset(buf2,0,sizeof(buf2));
        ssize_t sret1=read(fd1,buf1,sizeof(buf1));
        ssize_t sret2=read(fd2,buf2,sizeof(buf2));
        if(sret1!=sret2){
            printf("两个文件内容不一致!\n");
            break;
        }else if(memcmp(buf1,buf2,sret2)!=0){
            printf("两个文件内容不一致!\n");
            break;
        }else if(sret1 == 0){
            printf("两个文件内容相同!\n");
            break;
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}
