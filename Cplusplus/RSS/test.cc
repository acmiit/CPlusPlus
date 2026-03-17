#include "tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include<string>
#include <cstring>
#include <ctime>
#include<iostream>
#include<regex>
using namespace std;
using namespace tinyxml2;
int test0(){

    XMLDocument doc;
	doc.LoadFile( "coolshell.xml" );
    if(doc.ErrorID()){
        cerr<<"LoadFile error"<<endl;
        return -1;
    }
	XMLElement* itemElement = doc.FirstChildElement( "rss" )->FirstChildElement( "channel" )->FirstChildElement( "item" );
    
    // if(itemElement){
    while(itemElement){
        string title=itemElement->FirstChildElement("title")->GetText();
        string link=itemElement->FirstChildElement("link")->GetText();
        string description=itemElement->FirstChildElement("description")->GetText();
        string contentEncoded=itemElement->FirstChildElement("content:encoded")->GetText();
        // cout<<"title:"<<title<<endl;
        // cout<<"link:"<<link<<endl;
        // cout<<"description:"<<description<<endl;
        // cout<<"contentEncoded:"<<contentEncoded<<endl;

        regex rg("<[^>]*>");
        description=regex_replace(description,rg,"");
        contentEncoded=regex_replace(contentEncoded,rg,"");
        cout<<"title:"<<title<<endl;
        cout<<"link:"<<link<<endl;
        cout<<"description:"<<description<<endl;
        cout<<"contentEncoded:"<<contentEncoded<<endl;
        itemElement=itemElement->NextSiblingElement("item");
    }


	return doc.ErrorID();
}
int main(){
    test0();

}