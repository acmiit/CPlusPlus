#include<54func.h>
int main (int argc,char *argv[]){
    // ./9_fileno file1
    ARGS_CHECK(argc,2);
    FILE *fp=fopen(argv[1],"r+");
    ERROR_CHECK(fp,NULL,"fopen");
    int fd=fileno(fp);
    ssize_t sret= write(fd,"hello",5);
    printf("sret=%ld\n",sret);
    fclose(fp);
    return 0;
}
