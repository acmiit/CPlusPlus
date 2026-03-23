#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
void test(){
    vector<int> vec={1,3,5,7,4,67,11};
    vector<int>::iterator it=vec.begin();
    for(;it!=vec.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    //反向遍历
    vector<int>::reverse_iterator rit=vec.rbegin();
    for(;rit!=vec.rend();rit++){
        cout<<*rit<<" ";
    }
    cout<<endl;
}
int main(){
    test();
    return 0;
} 