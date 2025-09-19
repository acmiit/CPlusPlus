#include<54func.h>
int main(int argc,char *argv[]){
    //1_homework file1 file2
    ARGS_CHECK(argc,3);
    int fd1=open(argv[1],O_RDONLY);
    int fd2=open(argv[2],O_RDONLY);

    char buf1[4096],buf2[4096];
    while(1){
        memset(buf1,0,sizeof(buf1));
        memset(buf2,0,sizeof(buf2));
        ssize_t sret1=read(fd1,buf1,sizeof(buf1));
        ssize_t sret2=read(fd2,buf2,sizeof(buf2));
        if(sret1!=sret2){
            printf("Not the same!\n");
            break;
        }else if(memcmp(buf1,buf2,sret1)!=0){
            printf("Not the same!\n");
            break;

        }else if(sret1==0){
            printf("The same!\n");
            break;
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}