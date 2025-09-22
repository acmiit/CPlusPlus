#include<54func.h>
int main (int argc,char *argv[]){
    // ./11_redirect file1
    ARGS_CHECK(argc,2);
    printf("You can see me!\n");
    close(STDOUT_FILENO);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("fd = %d\n",fd);
    printf("You can't see me!\n");
    close(fd);
    return 0;
}
