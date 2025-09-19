#include<54func.h>
int main(int argc,char *argv[]){
    //./2_homework file1
    ARGS_CHECK(argc,2);
    char buf[10000];
    memset(buf,'1',sizeof(buf));
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
    for(int i=0;i<100;i++){
        write(fd,buf,sizeof(buf));
    }
    close(fd);
    return 0;
}