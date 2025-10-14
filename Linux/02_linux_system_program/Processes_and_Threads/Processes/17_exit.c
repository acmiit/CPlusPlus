#include<54func.h>
int func(){
    // exit(12);
    _exit(123);
}
int main(){
    printf("Can you see me 1 !\n");
    func();
    printf("Can you see me 2 !\n");
    return 0;
}