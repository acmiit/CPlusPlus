#include<54func.h>
int main(int argc,char *argv[]){
    FILE *fp=popen("./scanf","w");
    ERROR_CHECK(fp,NULL,"popen");
    fwrite("5 6",1,3,fp);
    pclose(fp);
    return 0;
}