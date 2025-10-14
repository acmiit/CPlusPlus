#include<54func.h>
int main(int argc,char* argv[]){
    // .9_fork_share file1
    //先open再fork访问的是同一个文件对象
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    if(fork()){
        sleep(1);
        write(fd,"world",5);
    }else{
        write(fd,"hello",5);
    }
    return 0;
}