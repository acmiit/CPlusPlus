#include<stdio.h>
void print(int j){
    printf("I am print j=%d\n",j);
}
int main(){
    int *p;
    int arr[3]={1,2,3};
    int j=10;
    arr[2]=4;
    p=arr;
    print(j);
    for(int i=0;i<5;i++){
        printf("Hello world!\n");
    }
    return 0; 
}