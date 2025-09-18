#include<54func.h>
int main(int argc,char * argv[]){
    // ./2_fread file1
    ARGS_CHECK(argc,2);
    int ret =chmod(argv[1],0664);
    ERROR_CHECK(ret,-1,"chmod");
    return 0;
}