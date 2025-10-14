#include<54func.h>
int main(int argc,char*argv[]){
    //与 5_fork.c不同的是第一个printf去掉了\n
    //相比于不同是 打印了两次Hello 结果为：Helloworkd Helloworld 
    printf("Hello");
    fork();
    printf("world\n");
    return 0;
}