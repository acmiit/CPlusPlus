#include<54func.h>
typedef struct train_s{
    int head;
    char data[4096];
}train_t;
int main(int argc,char *argv[]){
    // ./3_08homework_B 1.pipe
    ARGS_CHECK(argc,2);
    int fdr_pipe=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr_pipe,-1,"open pipe");

    train_t train;
    read(fdr_pipe,&train.head,sizeof(train.head));
    read(fdr_pipe,train.data,train.head);

    // printf("train.data=%s train.head=%d\n",train.data,train.head);

    char filename[1024]={0};
    memcpy(filename,train.data,train.head);
    char path[1024]={0};
    char dir[]="dir1/";
    mkdir(dir,0777);
    sprintf(path,"%s%s%s",dir,"/",filename);
    // printf("filename=%s\n",filename);
    int fdw=open(path,O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fdw,-1,"open file");
    read(fdr_pipe,&train.head,sizeof(train.head));
    read(fdr_pipe,train.data,train.head);  
    write(fdw,train.data,train.head); 
    close(fdr_pipe);
    close(fdw);
    return 0;
}