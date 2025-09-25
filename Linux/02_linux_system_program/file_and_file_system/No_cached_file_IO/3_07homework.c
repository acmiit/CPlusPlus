#include<54func.h>
#include<ctype.h>
int main (int argc,char *argv[]){
    // ./3_07homework file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    ftruncate(fd,500);
    char *p=(char *)mmap(NULL,500,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    for(int i=0;i<500;i++){
        if(p[i]>='a'&&p[i]<='z'){
            p[i]-=32;
        }else if(ispunct(p[i])){
            p[i]=' ';
        }
    }
    munmap(p,500);
    close(fd);
    return 0;
}
