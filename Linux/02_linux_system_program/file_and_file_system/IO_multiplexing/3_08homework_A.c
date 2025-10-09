#include<54func.h>
typedef struct train_s{
    int head;
    char data[4096];
}train_t;
int main(int argc,char *argv[]){
    // ./3_08homework_A 1.pipe file
    ARGS_CHECK(argc,3);
    int fdw_pipe=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw_pipe,-1,"open pipe");

    train_t train;
    train.head=strlen(argv[2]);
    memcpy(train.data,argv[2],train.head);
    write(fdw_pipe,&train.head,sizeof(train.head));
    write(fdw_pipe,train.data,train.head);
    // printf("train.data=%s train.head=%d\n",train.data,train.head);

    int fdr=open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open file");
    ssize_t sret = read(fdr,train.data,sizeof(train.data));
    train.head=sret;
    write(fdw_pipe,&train.head,sizeof(train.head));
    write(fdw_pipe,train.data,train.head);   
    close(fdw_pipe);
    close(fdr);
    return 0;
}