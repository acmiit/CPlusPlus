#include<54func.h>
int main (int argc,char *argv[]){
    // ./12_dup file1
    ARGS_CHECK(argc,2);
    int oldfd=open(argv[1],O_RDWR);
    int newfd=dup(oldfd);
    printf("oldfd=%d\n",oldfd);
    printf("newfd=%d\n",newfd);
    ssize_t sret_old=write(oldfd,"Hello",5);
    ssize_t sret_new=write(newfd,"World",5);
    close(oldfd);
    close(newfd);
    return 0;
}
