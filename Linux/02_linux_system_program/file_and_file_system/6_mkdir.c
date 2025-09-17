#include<54func.h>
int main(int argc,char * argv[]){
    // ./6_mkdir dir2
    ARGS_CHECK(argc,2);
    int ret =mkdir(argv[1],0777);
    ERROR_CHECK(ret,-1,"mkdir");
    return 0;
}