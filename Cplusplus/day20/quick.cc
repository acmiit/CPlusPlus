#include<iostream>
#include<vector>
using namespace std;
class Quick{
public:
    Quick(int *arr,int size)
    :_vec(arr,arr+size)
    {
        sort(0,size-1);
    }
    void sort(int left,int right){
        int pivot=partition(left,right);
        if(left<right){
            sort(0,pivot-1);
            sort(pivot+1,right);
        }

    }
    int partition(int left,int right){
        int pivot=_vec[left];
        while(left<right){
            while(left<right&&_vec[right]>pivot){
                right--;
            }
            if(left<right){
                _vec[left]=_vec[right];
                left++;
            }
            while(left<right&&_vec[left]<pivot){
                left++;
            }
            if(left<right){
                _vec[right]=_vec[left];
                right--;
            }
        }
        _vec[left]=pivot;
        return left;
    }
    void print(){
        for(auto number:_vec){
            cout<<number<<" ";
        }
        cout<<endl;
    }
private:
    vector<int> _vec;
};
int main(){
    int arr[]={7,6,5,4,1,2,3,5,8,9};
    Quick qu(arr,sizeof(arr)/sizeof(arr[0]));
    qu.print();
    return 0;
}