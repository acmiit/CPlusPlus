#include<iostream>
#include"tinyxml2.h"
using namespace tinyxml2;
int main(){
    XMLDocument doc;
    doc.LoadFile("test.xml"); //加载xml文件 ，解析
    XMLElement *root=doc.FirstChildElement("sites"); //找到第一个孩子为sites
    for(XMLElement *site=root->FirstChildElement("site");site;site=site->NextSiblingElement("site")){
        XMLElement * name=site->FirstChildElement("name");
        XMLElement *url=site->FirstChildElement("url");
        std::cerr<<"name: "<<name->GetText()<<" url: "<<url->GetText()<<"\n";
    }
    return 0;
}