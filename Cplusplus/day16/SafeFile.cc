#include<iostream>
#include<string>
using namespace std;
class SafeFile{
public:
    SafeFile(FILE *fp)
    :_fp(fp)
    {
        cout<<"SafeFile(FILE *)"<<endl;
    }
    void write(const string & mag){
        fwrite(mag.c_str(),1,mag.size(),_fp);
    }

    ~SafeFile(){
        if(_fp){
            fclose(_fp);
            cout<<"fclose(_fp)"<<endl;
        }
        cout<<"~SafeFile()"<<endl;
    }
private:
    FILE *_fp;
};
void test0(){
    string mag("hello world");
    SafeFile sf(fopen("SafeFile.txt","a+"));
    sf.write(mag);
}
int main(){
    test0();
    return 0;
}