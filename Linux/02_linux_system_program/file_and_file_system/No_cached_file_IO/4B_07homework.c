#include<54func.h>
int main (int argc,char *argv[]){
    // ./4B_07homework 1.pipe
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    char buf[1024]={0};
    ssize_t sret=read(fdr,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    close(fdr);
    return 0;
}
