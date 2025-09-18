#include<54func.h>
int main(int argc,char *argv[]){
    // ./2_read file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    char buf[1024]={0}; //read之前先清空
    memset(buf,0,sizeof(buf));
    int ret=read(fd,buf,1024);
    ERROR_CHECK(ret,-1,"read");
    printf("ret=%d buf=%s\n",ret,buf);
    close(fd);
    return 0;

}