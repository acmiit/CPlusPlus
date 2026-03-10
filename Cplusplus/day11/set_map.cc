#include<set>
#include<map>
#include<utility>
#include<string>
#include<iostream>
using namespace std;
void checkFind(const map<int,string> &rhs,int key){
    auto it=rhs.find(key);
    if(it==rhs.end()){
        cout<<"该元素不在map中"<<endl;
    }else{
        cout<<"该元素在map中"<<endl;
        cout<<it->first<<" "<<it->second<<endl;
    }
}

int main(){
    set<int> nums1;
    set<int> nums2{2,3,2,1,9,3,7,0,1};
    set<int> nums3=nums2;
    set<int> nums4(nums2.begin(),nums2.end());

    //会自动排序（从小到大，无重复元素）
    auto it=nums2.begin();
    for(;it!=nums2.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    //set 的查找操作
    cout<<nums2.count(9)<<endl;
    cout<<nums2.count(10)<<endl;

    auto it2=nums2.find(1);
    cout<<*it2<<endl;
    //找不到就返回尾后迭代器
    it2=nums2.find(8);
    if(it2==nums2.end()){
        cout<<"hello"<<endl;
    }
    pair<int,string> pair_nums={1,"wangdao"};
    cout<<pair_nums.first<<" "<<pair_nums.second<<endl; 

    //set的插入操作
    //插入一个元素
    auto ret =nums2.insert(1);
    if(ret.second){
        cout<<"插入成功"<<endl;
        cout<<*(ret.first)<<endl; 
    }else{
        cout<<"插入失败，元素已经存在"<<endl;
        cout<<*(ret.first)<<endl;
    }
     //插入多个元素
     int arr[5]={18,41,35,2,99};
     //传入首迭代器和尾后迭代器
     nums2.insert(arr,arr+5);
     for(auto & nu:nums2){
        cout<<nu<<" ";
    }
    cout<<endl;

    //传入大括号列表 
    nums2.insert({100,1,111});
    for(auto & nu:nums2){
       cout<<nu<<" ";
   }
   cout<<endl;

   cout<<"--------------------"<<endl;

   map<int,string> number={
    {1,"hello"},
    {2,"world"},
    {3,"wangdao"},
    pair<int,string>(4,"hubei"),
    pair<int ,string>(5,"wangdao"),
    make_pair(9,"shenzhen"),
    make_pair(3,"beijing"),
    make_pair(6,"shanghai")
   };
   //对map进行遍历
   for(auto & nu:number){
    cout<<nu.first<<" "<<nu.second<<endl;
   }
   cout<<endl;
//    auto it=number.begin();
   map<int,string>::iterator it3=number.begin();
   for(;it3 != number.end();++it3){
    cout<<it3->first<<" "<<it3->second<<endl;
   }

   //map中进行查找
   size_t cnt1=number.count(1);
   size_t cnt2=number.count(10);
   cout<<cnt1<<endl;
   cout<<cnt2<<endl;

   map<int,string>::iterator it4=number.find(1);
   auto it5=number.find(10);
   checkFind(number,10);
   cout<<endl;
   checkFind(number,5);
   cout<<endl;
    //map插入单个元素
    pair<map<int,string>::iterator,bool> ret1=number.insert(pair<int,string>(7,"nanjing"));
    if(ret1.second){
        cout<<"该元素插入成功！"<<endl;
        cout<<ret1.first->first<<" "<<ret1.first->second<<endl;
    }else{
        cout<<"该元素插入失败！"<<endl;
    }
    cout<<endl;
    //插入多个元素
    //迭代器方式
    map<int ,string> number2={{1,"beijing"},{18,"shanghai"}};
    number2.insert(number.begin(),number.end());
    for(auto & nu:number2){
        cout<<nu.first<<" "<<nu.second<<endl;
       }
    cout<<endl;
    //列表方式
    number2.insert({{4,"guangzhou"},{22,"hello"}});
    for(auto & nu:number2){
        cout<<nu.first<<" "<<nu.second<<endl;
       }
    cout<<endl;
    //支持写操作
    //如果访问的key不存在，会插入一个元素到map，value为空则按默认方式构造
    return 0;
}