#include<iostream>
#include<iterator>
#include<vector>
#include<list>
#include<set>
#include<algorithm>
using namespace std;
void test(){
    vector<int> vec;
    istream_iterator<int> isi(cin);
    // copy(isi,istream_iterator<int>(),back_inserter(vec));
    copy(isi,istream_iterator<int>(),back_insert_iterator<vector<int>>(vec));
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
}
void test1(){
    vector<int> vec={1,3,7,9,5};
    list<int> lst={4,6,8,2,10};
    // copy(lst.begin(),lst.end(),back_inserter(vec));
    //back_inserter调用的是back_insert_iterator
    // copy(lst.begin(),lst.end(),back_insert_iterator<vector<int>>(vec));
    // copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
    // cout<<endl;

    //头插法 
    // copy(vec.begin(),vec.end(),front_inserter(lst));
    // copy(vec.begin(),vec.end(),front_insert_iterator<list<int>>(lst));
    // copy(lst.begin(),lst.end(),ostream_iterator<int>(cout," "));
    // cout<<endl;

    set<int> setNumber={1,10,40,50,90,12};
    auto it =setNumber.begin();
    copy(vec.begin(),vec.end(),inserter<set<int>>(setNumber,it));
    copy(setNumber.begin(),setNumber.end(),ostream_iterator<int>(cout," "));
}
int main(){
    test1();
    return 0;
} 