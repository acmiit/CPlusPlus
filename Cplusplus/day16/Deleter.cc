#include<iostream>
#include<string>
#include<memory>
using namespace std;
void test0(){
    string msg="hello,world\n";
    FILE *p=fopen("res1.txt","a+");
    fwrite(msg.c_str(),1,msg.size(),p);
    fclose(p);
}
struct FILECloser
{
    void operator()(FILE *fp){
        if(fp){
            fclose(fp);
            cout<<"fclose(fp)"<<endl;
        }
    }
};


void test1(){
    string msg="hello,world\n";
    unique_ptr<FILE,FILECloser> up(fopen("res1.txt","a+"));
    fwrite(msg.c_str(),1,msg.size(),up.get());

}
int main(){
    // test0();
    test1();
    return 0;
}