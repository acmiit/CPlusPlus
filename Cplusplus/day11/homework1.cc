#include<iostream>
#include<map>
#include<set>
#include<math.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;
class Dictionary{
public:
    Dictionary(){}
    ~Dictionary(){}
    string isword(const string &word);
    void read(const string &filename);
    void store(const string &filename);
    void findword(const string &word);
private:
    map<string,int> _dict;
    map<int,string> _dictLine;
    map<string,set<int>> _wordLine;
};
string Dictionary::isword(const string &word){
    int word_len=word.size();
    for(int i=0;i<word_len;i++){
        if(!isalpha(word[i])){
            return string();
        }
    }
    return word;
}
void Dictionary::read(const string &filename){
    ifstream ifs(filename);
    if(!ifs){
        cerr<<"open"<<filename<<"fail"<<endl;
        return ;
    }
    string line;
    int i=0;
    while(getline(ifs,line)){
        i++;
        _dictLine[i]=line;
        istringstream iss(line);
        string word;
        while(iss>>word){
            string newword=isword(word);
            if(newword!=string()){
                auto it=_dict.find(newword);
                if(it==_dict.end()){
                    _dict[newword]=1;
                    _wordLine[newword].insert(i);
                }else{
                    _dict[newword]+=1;
                    _wordLine[newword].insert(i);
                }
            }
        }
    }
    ifs.close();
}


void Dictionary::store(const string &filename){
    ofstream ofs(filename);
    if(!ofs){
        cerr<<"open"<<filename<<"fail"<<endl;
        return ;
    }
    for(auto & nu:_dict){
        ofs<<nu.first<<" "<<nu.second<<endl;
    }
    ofs.close();
}

void Dictionary::findword(const string &word){
    if(_dict.find(word)!=_dict.end()){
        if(_dict[word]==1){
            cout<<word<<" occurs "<<_dict[word]<<" time"<<endl;
        }else{
            cout<<word<<" occurs "<<_dict[word]<<" times"<<endl;
        }
    }
    for(auto & nu:_wordLine[word]){
        cout<<"(line "<<nu<<")"<<_dictLine[nu]<<endl;
    }
}
int main(){
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dict.txt");
    dict.findword("adonibezek");
    return 0;
}