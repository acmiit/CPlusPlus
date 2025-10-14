#include<54func.h>
int main(int argc,char*argv[]){
    int wstatus;
    if(fork()){
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("exit status = %d\n",WEXITSTATUS(wstatus));
        }else if (WIFSIGNALED(wstatus)){
            printf("abnormal quit, terminal signial = %d\n",WTERMSIG(wstatus));
        }
    }else{
        while(1){
            sleep(1);
        }
    }
    return 0;
}