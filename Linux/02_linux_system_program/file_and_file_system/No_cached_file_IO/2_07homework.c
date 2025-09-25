#include<54func.h>
int main (int argc,char *argv[]){
    // ./2_07homework file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY|O_TRUNC|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    char buf[10000];
    memset(buf,'1',sizeof(buf));
    for(int i=0;i<10;i++){
        write(fd,buf,sizeof(buf));
    }
    close(fd);
    return 0;
}
