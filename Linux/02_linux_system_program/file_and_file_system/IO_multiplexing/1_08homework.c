#include<54func.h>
int main(int argc,char *argv[]){
    // ./1_08homeowrk 1.pipe
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_RDWR);
    int fdr=open(argv[1],O_RDWR);
    printf("pip is opened!\n");
    fd_set rdset;
    fd_set wrset;
    char buf[4096]={0};
    int cnt=0;
    while(1){
        FD_ZERO(&wrset);
        FD_ZERO(&rdset);
        FD_SET(fdr,&rdset);
        FD_SET(fdw,&wrset);
        int ret = select(fdr+1,&rdset,&wrset,NULL,NULL);
        if(FD_ISSET(fdr,&rdset)){
            read(fdr,buf,1024);
            printf("read ready,cnt=%d,ret=%d\n",cnt++,ret);
        }
        if(FD_ISSET(fdw,&wrset)){
            write(fdw,buf,4096);
            printf("write ready,cnt=%d,ret=%d\n",cnt++,ret);
        }
        sleep(1);
    }
    return 0;
}