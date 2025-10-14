#include<54func.h>
int main(int argc,char* argv[]){
    // .10_open_after_fork_ file1
    //先fork再open,文件对象不共享
    ARGS_CHECK(argc,2);

    if(fork()){
        sleep(1);
        int fd = open(argv[1],O_RDWR);
        ERROR_CHECK(fd,-1,"open");
        write(fd,"world",5);
    }else{
        int fd = open(argv[1],O_RDWR);
        ERROR_CHECK(fd,-1,"open");
        write(fd,"hello",5);
    }
    return 0;
}