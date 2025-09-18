#include<54func.h>
int main(){
    // ./4_getcwd
    // char path[1024]={};
    // char *path=(char *)malloc(1024);
    // char *p=getcwd(path,1024);
    // ERROR_CHECK(p,NULL,"getcwd");
    char *p=getcwd(NULL,0);
    printf("cwd=%s\n",p);
    // free(path);
    return 0;
}