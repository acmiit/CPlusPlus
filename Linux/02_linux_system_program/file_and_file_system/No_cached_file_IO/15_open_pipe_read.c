#include<54func.h>
int main (int argc,char *argv[]){
    // ./15_open_pipe_read file1
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("read side is opened\n");
    char buf[1024]={0};
    ssize_t sret=read(fdr,buf,sizeof(buf));
    printf("sret=%ld,buf=%s\n",sret,buf);
    // close(fdr);
    return 0;
}
