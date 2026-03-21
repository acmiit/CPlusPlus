#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
class mapTofile
{
public:
    void buildMap(const string &filename){
        ifstream ifs(filename);
        if(!ifs){
            cerr<<"ifs open file fail!"<<endl;
        }
        string key,value;
        while(ifs>>key&&getline(ifs,value)){
            if(value.size()>1){
                _dict[key]=value;
            }else{
                throw runtime_error("no rule for " + key);
            }
        }
    }
    void transfile(const string &filename1,const string &filename2){
        ifstream infile(filename1);
        ofstream outfile(filename2);
        string line;
        while(getline(infile,line)){
            istringstream iss(line);
            string word;
            // string newword;
            while(iss>>word){
                if(_dict.find(word)!=_dict.end()){
                    word=_dict[word];
                }
                outfile<<word<<" ";
            }
            outfile<<endl;
        }

    }
private:
    map<string,string> _dict;
};
int main()
{
    mapTofile mTf;
    mTf.buildMap("map.txt");
    mTf.transfile("file.txt","file1.txt");
    return 0;
}