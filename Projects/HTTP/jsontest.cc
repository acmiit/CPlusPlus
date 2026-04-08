// test_json.cpp
#include <iostream>
#include <nlohmann/json.hpp>
using Json=nlohmann::json;
int main() {
    Json sites;
    sites["sites"].push_back({"site",{"name","王道论坛"},{"url","www.cskaoyan.com"}});
    sites["sites"].push_back({"site",{{"name","Google"},{"url","www.google.com"}}});
    sites["sites"].push_back({"site",{{"name","微博"},{"url","www.weibo.com"}}});
    std::cerr<<sites.dump()<<"\n";
    return 0;
}