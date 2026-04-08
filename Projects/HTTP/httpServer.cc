#include<54func.h>
#include<iostream>
#include<string>
using std::string;
using std::cerr;

class HttpServer{
public:
    HttpServer(const string &ip,unsigned short port)
    :_ip(ip)
    ,_port(port)
    ,_sockfd(-1)
    {}
    ~HttpServer(){}
    void start();
    void recvAndShow();
    string response();
private:
    string _ip;
    unsigned short _port;
    int _sockfd; 
};
void HttpServer::start(){
    _sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(_sockfd<0){
        perror("socket");
        exit(1);
    }
    int reuse=1;
    int ret = setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    if(ret<0){
        perror("setsockopt");
        exit(1);
    }
    struct sockaddr_in serveraddr;
    serveraddr.sin_addr.s_addr=inet_addr(_ip.c_str());
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(_port);

    ret=::bind(_sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    if(ret<0){
        perror("bind");
        exit(1);
    }
    listen(_sockfd,128);
}
void HttpServer::recvAndShow(){
    while(1){
        int netfd=accept(_sockfd,nullptr,nullptr);
        char buf[4096]={0};
        ssize_t sret=recv(netfd,buf,sizeof(buf),0);
        printf("sret= %ld, buf=%s\n",sret,buf);
        string resp=response();

        send(netfd,resp.c_str(),resp.size(),0);
        close(netfd);
    }
}
// string HttpServer::response(){
//     string startLine="HTTP/1.1 200 OK\r\n"; 
//     string headers="Server: MyHttpServer\r\n";
//     string body="<html> Hello world</html>";
//     headers+="Content-Type:text/html\r\n";
//     headers+="Content-Length:" + std::to_string(body.size())+"\r\n";
//     string emptyLine="\r\n";
//     return  startLine+headers+emptyLine+body;

// }
// string HttpServer::response(){
//     string startLine="HTTP/1.1 200 OK\r\n"; 
//     string headers="Server: MyHttpServer\r\n";

//     int fd=open("test.html",O_RDWR);
//     char buf[4096]={0};
//     read(fd,buf,sizeof(buf));
//     string body=buf;
//     headers+="Content-Type:text/html\r\n";
//     headers+="Content-Length:" + std::to_string(body.size())+"\r\n";
//     string emptyLine="\r\n";
//     return  startLine+headers+emptyLine+body;

// }

string HttpServer::response(){
    string startLine="HTTP/1.1 302 Found\r\n"; 
    string headers="Server: MyHttpServer\r\n";
    headers+="Content-Type:text/html\r\n";
    headers+="Location: http://www.baidu.com\r\n";
    string emptyLine="\r\n";
    return  startLine+headers+emptyLine;

}
int main(){
    HttpServer server("172.22.195.222",8888);
    server.start();
    server.recvAndShow();
    return 0;
}