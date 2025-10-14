#include<54func.h>
int main(int argc,char*argv[]){
    printf("You can see me!\n");
    printf("pid = %d\n",getpid());
    execl("add",  //add是exe的路径
        "./add","3","4", //./add 是命令参数的一部分
        NULL); //额外补充一个NULL
    printf("You can't see me!\n");
    return 0;
}