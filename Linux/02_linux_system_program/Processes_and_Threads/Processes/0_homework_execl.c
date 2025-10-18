#include<54func.h>
int main(int argc,char *argv[]){
    if(fork()){
        wait(NULL);
        printf("child is finished!\n");
    }else{
        printf("I am child\n");
        execl("readdir","./readdir",".",NULL);
    }
    return 0;
}