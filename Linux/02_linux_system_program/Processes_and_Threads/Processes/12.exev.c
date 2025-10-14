#include<54func.h>
int main(int argc,char*argv[]){
    printf("You can see me!\n");
    printf("pid = %d\n",getpid());
    char *argArr[]={
        "./add","3","4","NULL"
    };
    execv("add",argArr);
    printf("You can't see me!\n");
    return 0;
}