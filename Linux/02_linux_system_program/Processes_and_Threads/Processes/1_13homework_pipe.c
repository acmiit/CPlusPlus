#include<54func.h>
int main(int argc,char *argv[]){
    int fds[0];
    pipe(fds);

    //----------------------------读阻塞
    // if(fork()){
    //     close(fds[0]); 
    //     sleep(5);
    //     printf("sleep over!\n");
    //     write(fds[1],"hello",5);
    // }else{
    //     close(fds[1]);
    //     char buf[4096]={0};
    //     ssize_t sret=read(fds[0],buf,4096);
    //     printf("sret = %ld,buf = %s\n",sret ,buf);
    // }
    //----------------------------写阻塞
    // if(fork()){
    //     close(fds[0]); 
    //     char buf[4096];
    //     int cnt=0;
    //     while(1){
    //         write(fds[1],buf,4096);
    //         printf("parent cnt = %d\n",++cnt);
    //         sleep(1);
    //     }
    // }else{
    //     close(fds[1]);
    //     char buf[1024]={0};
    //     int cnt=0;
    //     while(1){
    //         read(fds[0],buf,1024);
    //         printf("child cnt = %d\n",++cnt);
    //         sleep(1);
    //     }
    // }
   //先关闭读端，写端继续写入
    // if(fork()){
    //     close(fds[0]); 
    //     sleep(5);
    //     printf("sleep over!\n");
    //     write(fds[1],"hello" ,5);
    //     printf("Can you see me !\n");
    //     wait(NULL);
    // }else{
    //     close(fds[1]);
    //     close(fds[0]);
    //     while(1){
    //         sleep(1);
    //     }
    // }
    //先关闭写端，读端继续读
    if(fork()){
        close(fds[0]); 
        close(fds[1]);
        wait(NULL);
    }else{
        close(fds[1]);
        char buf[1024]={0};
        sleep(1);
        printf("sleep over!\n");
        while(1){
            ssize_t sret = read(fds[0],buf,sizeof(buf));
            printf("sret = %ld,buf=%s\n",sret,buf);
        }
    }
    return 0;
}