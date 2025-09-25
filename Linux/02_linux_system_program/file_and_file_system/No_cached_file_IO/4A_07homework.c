#include<54func.h>
int main (int argc,char *argv[]){
    // ./4A_07homework 1.pipe
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("Helloworld 1\n");
    int backupfd=10;
    dup2(STDOUT_FILENO,backupfd);
    dup2(fdw,STDOUT_FILENO);
    printf("Helloworld 2\n");
    dup2(backupfd,STDOUT_FILENO);
    printf("Helloworld 3\n");
    close(fdw);
    return 0;
}
