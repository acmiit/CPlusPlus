#include<54func.h>
typedef struct student_s 
{
    int id;
    char name[30];
    float score;
}student_t;

int main(int argc,char *argv[]){
    // /.0_homework file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    student_t stu[3]={{1,"zhangsan",66.6},{2,"lisi",77.7},{3,"wanglaowu",88.8}};
    write(fd,stu,sizeof(stu));
    lseek(fd,0,SEEK_SET);
    student_t arr[3];
    read(fd,arr,sizeof(stu));
    for(int i=0;i<sizeof(stu)/sizeof(stu[0]);i++){
        printf("id=%d name=%s score=%.1f\n",arr[i].id,arr[i].name,arr[i].score);
    }
    close(fd);
    return 0;
}