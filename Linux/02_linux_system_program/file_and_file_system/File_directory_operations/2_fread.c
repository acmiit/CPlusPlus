#include<54func.h>
int main(int argc,char * argv[]){
    // ./2_fread file1
    ARGS_CHECK(argc,2);
    FILE *fp=fopen(argv[1],"r+");
    ERROR_CHECK(fp,NULL,"fopen");

    char buf[1024]={0};
    fread(buf,1,sizeof(buf),fp);
    printf("buf=%s\n",buf);
    return 0;
}