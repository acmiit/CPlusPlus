#include<54func.h>
void tree(const char * path,int deep){
    DIR *dirp=opendir(path);
    if(dirp == NULL){
        return ;
    }

    struct stat statbuf;
    struct dirent *pdirent;
    while((pdirent=readdir(dirp))!= NULL){
        char full_path[1024];
        snprintf(full_path,sizeof(full_path),"%s/%s",path,pdirent->d_name);
        if(stat(full_path,&statbuf)==-1){
            continue;
        }
        if (S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(pdirent->d_name,".")==0 || strcmp(pdirent->d_name,"..")==0)
                continue;
            for(int i=0;i<deep;i++)
                printf(" ");
            printf("|-- %s/\n",pdirent->d_name);
            tree(full_path,deep+1);
        }
        else{
            for(int i=0;i<deep;i++)
                printf(" ");
            printf("|-- %s\n",pdirent->d_name);
        }

        
    }
    closedir(dirp);

}
int main(int argc,char * argv[]){
    const char *path = (argc > 1) ? argv[1] : ".";
 
    tree(path,0);
    return 0;
}