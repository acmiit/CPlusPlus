#include<54func.h>
int main (int argc,char *argv[]){
    // ./7_to_upper file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret =ftruncate(fd,12);
    ERROR_CHECK(ret,-1,"ftruncate");
    char *p=(char *)mmap(NULL,12,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap");

    for(int i=0;i<12;i++)
    {
        if(p[i]<='z' && p[i]>='a'){
            p[i]-=32;
        }
    }   
    munmap(p,12);
    close(fd);
    return 0;
}
