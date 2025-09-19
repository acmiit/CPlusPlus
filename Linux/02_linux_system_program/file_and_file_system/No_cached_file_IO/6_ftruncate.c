#include<54func.h>
int main(int argc,char *argv[]){
    // ./6_ftruncare file1
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret = ftruncate(fd,20);
    ERROR_CHECK(ret,-1,"ftruncate");
    close(fd);
    return 0; 
}