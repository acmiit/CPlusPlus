#include<54func.h>
int main(int argc,char *argv[]){
    // ./4_write file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY);
    ERROR_CHECK(fd,-1,"open");
    int ret=write(fd,"How are you?\n",14);
    ERROR_CHECK(ret,-1,"write");
    close(fd);
    return 0;
}