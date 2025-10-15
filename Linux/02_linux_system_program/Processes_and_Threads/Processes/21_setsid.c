#include<54func.h>
//终端断开，对应的会话中的进程· 会终止
int main(int argc,char *argv[]){
    if(fork()){
        exit(0);
    }else{
        printf("Before, sid=%d\n",getsid(0));
        setsid(); //只有非组长才能调用
        printf("After, sid=%d\n",getsid(0));
    }
    return 0;
}