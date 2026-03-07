#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> num1{1,2,3,4,5};
    vector<int> num2{6,7,8,9,10};
    vector<vector<int>> vecs{num1,num2};
    cout<< *vecs.begin()->begin()<<endl;
    return 0;
} 