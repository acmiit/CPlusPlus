#include<54func.h>
void Daemon(){
    //新建会话
    if(fork()){
        exit(0);
    }
    setsid();
    //关闭设备
    for(int i=0;i< 64;i++){
        close(i);
    }
    //修改环境属性
    chdir("/");
    umask(0);

}
int main(int argc,char* argv[]){
    Daemon();
    for(int i=0;i<20;i++){
        syslog(LOG_INFO,"I am Daemon,i=%d\n",i);
    }
    return 0;
}