#include<iostream>
#include<math.h>
#include<string>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;
string longestCommonPrefix(vector<string>& strs) {
    int strs_len=strs.size();
    vector<string> results(strs_len);
    results[0]=strs[0];
    for(int i=1;i<strs_len;i++){
        int j=0;
        while(j<results[i-1].size()&&j<strs[i].size()){
            if(results[i-1][j]==strs[i][j]){
                j++;
            }else{
                break;
            }
        }
        results[i]=strs[0].substr(0, j);
    }
    if(results[strs_len-1].empty()){
        return "";
    }else{
        return results[strs_len-1];
    }

}
int main(){
    vector<string> strs={"dog","racecar","car"};
    cout<<longestCommonPrefix(strs)<<endl;
    return 0;
}