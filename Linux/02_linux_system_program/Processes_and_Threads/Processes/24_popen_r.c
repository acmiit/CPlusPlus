#include<54func.h>
int main(int argc,char *argv[]){
    FILE *fp=popen("./printf","r");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[1024]={0};
    fread(buf,1,sizeof(buf),fp);
    printf("buf = %s\n",buf);
    pclose(fp);
    return 0;
}