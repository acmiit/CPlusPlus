#include<iostream>
#include<math.h>
#include<string>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;
bool isValid(string s) {
    vector<char> stack;
    for(int i=0;i<s.size();i++){
        if(s[i]=='('||s[i]=='['||s[i]=='{'){
            stack.push_back(s[i]);
        }else{
            if(stack.empty()){
                return false;
            }else{
                if(s[i]==')'&&stack.back()=='('||s[i]==']'&&stack.back()=='['||s[i]=='}'&&stack.back()=='{'){
                    stack.pop_back();
                }else{
                    return false;
                }
            }
        }
    }
    return stack.empty();
}
int main(){
    cout<<isValid("([)]")<<endl;
    return 0;
}