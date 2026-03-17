#include<iostream>
#include<math.h>
#include<string>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;
void moveZeroes(vector<int>& nums) {
    int count=0;
    for(int i=0;i<nums[i];i++){
        if(nums[i]==0){
            count++;
        }else{
            nums[i-count]=nums[i];
            cout<<i<<endl;
        }
    }
}
int main(){
    vector<int> nums{0,1,0,3,13};
    moveZeroes(nums);
    return 0;
}