#include <iostream>
 
#include<list>
using namespace std;
 
// 重载 < 运算符
bool operator<(const list<int>::iterator& lhs, const list<int>::iterator& rhs) {
    return &(*lhs) < &(*rhs);
}
 
 
int main(int argc, char * argv[])
{
    list<int> lst = {1, 3, 5, 7, 9, 8, 6, 4, 3, 4, 4, 4, 3}; 
    list<int>::iterator iter1 = lst.begin(),iter2 = lst.end(); 
    while(iter1 < iter2)
    {    
        //....
        cout << "iter1 = " << *iter1 << " " << endl;
        ++iter1;
    }
    cout << endl;
    return 0;
}