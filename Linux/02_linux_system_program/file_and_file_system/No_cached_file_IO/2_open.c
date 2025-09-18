#include<54func.h>
int main(int argc,char *argv[]){
    // ./2_open file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("fd=%d\n",fd);
    close(fd);
    return 0;

}