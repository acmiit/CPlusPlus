#include<54func.h>
int main(int argc,char argv[]){
    int fds[2];
    pipe(fds);
    printf("fds[0]=%d, fds[1]=%d\n",fds[0],fds[1]);
    char buf[1024];
    write(fds[1],"Hello",5);
    read(fds[0],buf,sizeof(buf));
    printf("buf = %s\n",buf);

    close(fds[0]);
    close(fds[1]);
    return 0;
}