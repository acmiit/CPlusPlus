#include"Line.hpp"
#include<iostream>
using namespace std;
int main(){
    cout<<sizeof(Line)<<endl;
    Line line(1,2,3,4);
    line.printLine();
    return 0;
}