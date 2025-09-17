#include<54func.h>
int main(int argc,char * argv[]){
    // ./7_rmdir dir2
    ARGS_CHECK(argc,2);
    int ret =rmdir(argv[1]);
    ERROR_CHECK(ret,-1,"rmdir");
    return 0;
}