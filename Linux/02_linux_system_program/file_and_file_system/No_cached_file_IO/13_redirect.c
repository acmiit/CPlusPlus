#include<54func.h>
int main (int argc,char *argv[]){
    // ./13_redirect file1
    ARGS_CHECK(argc,2);
    printf("You can see me!\n");
    int fd =open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    close(STDOUT_FILENO);
    int newfd=dup(fd);
    printf("fd = %d\n",fd);
    printf("newfd = %d\n",newfd);
    printf("You can't see me!\n");
    return 0;
}
