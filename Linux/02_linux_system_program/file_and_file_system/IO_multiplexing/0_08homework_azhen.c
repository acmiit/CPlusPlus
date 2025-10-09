#include<54func.h>
int main(int argc,char *argv[]){
    // ./0_08homework_azhen 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,"-1","open read");
    int fdw=open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,"-1","open write");
    printf("azhen connected!\n");
    char buf[4096];
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(fdr,&rdset)){
            memset(buf,0,sizeof(buf));
            ssize_t ret = read(fdr,buf,sizeof(buf));
            if(ret ==0 ){
                printf("Hehe!\n");
                break;
            }
            printf("buf=%s\n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            ssize_t ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){
                write(fdw,"nishigehaoren!",13);
                break;
            }
            time_t now=time(NULL);
            char *p=ctime(&now);
            char newbuf[8192]={0};
            sprintf(newbuf,"%s %s",p,buf);
            write(fdw,newbuf,strlen(newbuf));
        }

    }
    return 0;
}