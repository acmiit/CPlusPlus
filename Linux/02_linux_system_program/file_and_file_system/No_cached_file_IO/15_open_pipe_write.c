#include<54func.h>
int main (int argc,char *argv[]){
    // ./15_open_pipe_write file1
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("write side is opened\n");
    sleep(10);
    printf("write side sleep over!\n");
    write(fdw,"hello",5);
    while(1){
        sleep(1);
    }
    // close(fdw);
    return 0;
}
