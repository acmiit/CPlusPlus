#include<54func.h>
int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    DIR *dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * pdirent;
    while((pdirent = readdir(dirp)) !=NULL){
        printf("%s\n",pdirent->d_name);
    }
    closedir(dirp);
    return 0;
}