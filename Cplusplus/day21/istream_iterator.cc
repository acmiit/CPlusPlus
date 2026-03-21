#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include<set>
using namespace std;

void test()
{
    vector<int> numbers1{1, 3, 5};
    list<int> numbers2{20, 30, 40};
    // back_insert_iterator底层是调用了push_back
    copy(numbers2.begin(), numbers2.end(), back_insert_iterator<vector<int>>(numbers1));
    copy(numbers1.begin(), numbers1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // front_insert_iterator底层是调用了push_front
    copy(numbers1.begin(), numbers1.end(), front_insert_iterator<list<int>>(numbers2));
    copy(numbers2.begin(), numbers2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    set<int> numbers3{12, 13, 16, 13};
    auto sit = numbers3.begin();
    ++sit;
    // insert_iterator底层是调用了insert
    copy(numbers1.begin(), numbers1.end(), insert_iterator<set<int>>(numbers3, sit));
    copy(numbers3.begin(), numbers3.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
int main(){
    test();
    return 0;
}