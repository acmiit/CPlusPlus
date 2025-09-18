#include<54func.h>
void ls_al(const char * path){
    DIR *dirp=opendir(path);
    if(dirp == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct stat statbuf;
    struct dirent *pdirent;
    while((pdirent=readdir(dirp))!= NULL){
        char full_path[1024];
        sprintf(full_path,"%s%s%s",path,"/",pdirent->d_name);
        if(stat(full_path,&statbuf)==-1){
            perror("stat");
            exit(EXIT_FAILURE);
        }
        struct passwd *user=getpwuid(statbuf.st_uid);
        struct group *group=getgrgid(statbuf.st_gid);
        char permissions[11];
        permissions[0] = (S_ISDIR(statbuf.st_mode)) ? 'd' : '-';
        permissions[1] = (statbuf.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (statbuf.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (statbuf.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (statbuf.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (statbuf.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (statbuf.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (statbuf.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (statbuf.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (statbuf.st_mode & S_IXOTH) ? 'x' : '-'; 
        permissions[10] = '\0'; 
        char timeString[80];
        strftime(timeString, sizeof(timeString), "%b %d %H:%M", localtime(&statbuf.st_mtime));
     
        printf("%s %ld %s %10s %10ld %s %s\n", permissions, statbuf.st_nlink,
            user->pw_name, group->gr_name, statbuf.st_size, timeString, pdirent->d_name);
    }
    closedir(dirp);

}
int main(int argc,char * argv[]){
    const char *path = (argc > 1) ? argv[1] : ".";
 
    ls_al(path);
    return 0;
}