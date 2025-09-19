#include<54func.h>
int main(int argc,char *argv[]){
    // ./5_mycp file1 file2
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open read");
    int fdw=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fdw,-1,"open write");

    char buf[1024]={0};
    while(1){
        memset(buf,0,sizeof(buf));
        ssize_t retr=read(fdr,buf,sizeof(buf));
        if(retr==0)
            break;
        write(fdw,buf,retr);
    }
    close(fdr);
    close(fdw);
    return 0; 
}