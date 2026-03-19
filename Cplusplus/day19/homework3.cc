#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
template <typename T, typename Compare = std::less<T>> 
class HeapSort 
{ 
public:  
    HeapSort(T *arr, size_t size)
    :_vec(arr,arr+size)
    {
        sort();
    } 
    void heapAdjust(size_t parent,size_t len){
        size_t child=parent*2+1;
        T temp=_vec[parent];
        while(child<len){
            if(child+1<len&&_cmp(_vec[child],_vec[child+1])){
                ++child;
            }
            if(_cmp(temp,_vec[child])){
                _vec[parent]=_vec[child];
                parent=child;
                child=parent*2+1;
            }else{
                break;
            }
        }
        _vec[parent]=temp;
    }  
    void sort(){
        int len=_vec.size();
        for(int i=len/2-1;i>=0;i--){
            heapAdjust(i,len);
        }
        for(int i=len-1;i>0;i--){
            swap(_vec[0],_vec[i]);
            heapAdjust(0,i);
        }
    }
    void print(){
        for(auto &it:_vec){
            cout<<it<<" ";
        }
        cout<<endl;
    }
private:  
    vector<T> _vec;
    Compare _cmp;
};
int main(){
    int arr[] = {4, 1, 7, 3, 8, 5, 9, 2, 6};
    HeapSort<int> heapSort(arr, sizeof(arr) / sizeof(arr[0]));
    heapSort.print();
    return 0;
}