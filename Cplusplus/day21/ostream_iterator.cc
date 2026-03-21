#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
void test0(){
    vector<int> vec={1,3,5,7,9,4};
    ostream_iterator<int> osi(cout,"\n");
    copy(vec.begin(),vec.end(),osi);
}
int main(){
    test0();
    return 0;
}