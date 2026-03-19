#include<iostream>
#include<vector>
#include <functional> // for std::less
using namespace std;
template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com= Compare())
    :_vec(arr,arr+size)
    {
        if(size>0)
            quick(0,size-1,com);
    }     
    void quick(int left, int right, Compare com){
        if(left<right){
            int qivot=partition(left,right,com);
            quick(left,qivot-1,com);
            quick(qivot+1,right,com);
        }
    }     
    int partition(int left, int right, Compare &com){
        int pivot=_vec[left];
        int i=left;
        int j=right;
        while(i<j){
            while(i<j&&com(pivot,_vec[j])) j--;
            if(i<j) _vec[i++]=_vec[j];
            while(i<j&&com(_vec[i],pivot)) i++;
            if(i<j) _vec[j--]=_vec[i];
        }
        _vec[i]=pivot;
        return i;
    }     
    void print(){
        for(auto &it:_vec){
            cout<<it<<" ";
        }
        cout<<endl;
    }
private:    
    vector<T> _vec; 
};
int main(){
    int arr[] = {4, 65, 2, -31, 0, 99, 83, 782, 1};
    MyQsort<int> sorter(arr, sizeof(arr) / sizeof(arr[0]));
    sorter.print();
    return 0;
}