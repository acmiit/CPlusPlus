#include<iostream>
#include<vector>
using namespace std;
template <typename T, typename Compare = std::less<T>> 
class HeadSort{
public:
    HeadSort(T* arr,size_t size)
    :_vec(arr,arr+size)
    {
        sort();
    }
    void HeadAdjust(size_t parent,size_t len){
        size_t child=parent*2+1; //左节点
        T temp=_vec[parent];
        while(child<len){
            if(child+1<len&&_com(_vec[child],_vec[child+1])){
                child++;
            }
            if(_com(temp,_vec[child])){
                _vec[parent]=_vec[child];
                _vec[child]=temp;
                temp=_vec[parent];
            }else{
                break;
            }
        }
        _vec[parent]=temp;
    }
    void sort(){
        size_t len=_vec.size();
        for(int i=_vec.size()/2-1;i>=0;i--){
            HeadAdjust(i,len);
        }
        for(int i=len-1;i>0;i--){
            swap(_vec[i],_vec[0]);
            HeadAdjust(0,i);
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
    Compare _com;
};
int main(){
    int number[]={10,1,5,7,3,2,4,6,8,6,4,76,8};
    HeadSort<int> hd(number,sizeof(number)/sizeof(number[0]));
    hd.print();
    return 0;
}