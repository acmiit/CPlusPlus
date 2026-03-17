#include "tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include<string>
#include <cstring>
#include <ctime>
#include<iostream>
#include<regex>
#include<fstream>
using namespace std;
using namespace tinyxml2;
struct RSSitem
{
    string title;
    string link;
    string description;
    string content;
};
class RSS{
public:
    RSS(){}
    void parseRss(const string & filename) //解析
    {
        XMLDocument doc;
        //打开文件
        doc.LoadFile(filename.c_str() );
        //检查报错
        if(doc.ErrorID()){
            cerr<<"LoadFile error"<<endl;
            return ;
        }
        //根据标签进行一级级的查找
        XMLElement* itemElement = doc.FirstChildElement( "rss" )->FirstChildElement( "channel" )->FirstChildElement( "item" );
        size_t idx=0;
        while(itemElement){
            //获取信息
            string title=itemElement->FirstChildElement("title")->GetText();
            string link=itemElement->FirstChildElement("link")->GetText();
            string description=itemElement->FirstChildElement("description")->GetText();
            string contentEncoded=itemElement->FirstChildElement("content:encoded")->GetText();
            
            //正则表达剔除标签
            regex rg("<[^>]*>");
            description=regex_replace(description,rg,"");
            contentEncoded=regex_replace(contentEncoded,rg,"");
            RSSitem rssitem;
            rssitem.title=title;
            rssitem.link=link;
            rssitem.description=description;
            rssitem.content=contentEncoded;
            itemElement=itemElement->NextSiblingElement("item");
            _rss.push_back(rssitem);
            idx++;
        }

    }
    void dump(const string & filename) //输出
    {
        ofstream ofs(filename);
        if(!ofs){
            cerr<<"open"<<filename<<"fail!"<<endl;
            return ;
        }
        for(size_t idx=0;idx<_rss.size();++idx){
            ofs<<"doc>\n\t<docid>"<<idx+1<<
            "</docid>\n\t<title>"<<_rss[idx].title<<
            "</title>\n\t<link>"<<_rss[idx].link<<
            "</link>\n\t<description>"<<_rss[idx].description<<
            "</description>\n\t<content>"<<_rss[idx].content<<"</content>\n</doc>"<<endl;
        }
        ofs.close();
    }
private:
    vector<RSSitem> _rss;
};
int test0(){
    RSS rss;
    rss.parseRss("coolshell.xml");
    rss.dump("wd.txt");
}
int main(){
    test0();

}