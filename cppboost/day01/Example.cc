#include<iostream>
using namespace std;
class Example{

};
void test(){
    cout<<"sizeof(Example)="<<sizeof(Example)<<endl;
    Example ex;
    Example ex1;
    Example ex2;
    Example ex3;
    //为了区分对象不一样 
    printf("&ex=%p\n",&ex);
    printf("&ex1=%p\n",&ex1);
    printf("&ex2=%p\n",&ex2);
    printf("&ex3=%p\n",&ex3);
}
int main(){
    test();
    return 0;
}