#include<54func.h>
int main(int argc,char * argv[]){
    // ./5_chdir dir1
    ARGS_CHECK(argc,2);
    printf("before chdir,cwd=%s\n",getcwd(NULL,0));
    int ret =chdir(argv[1]);
    printf("after chdir,cwd=%s\n",getcwd(NULL,0));
    ERROR_CHECK(ret,-1,"chdir");
    return 0;
}