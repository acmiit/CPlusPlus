#include<54func.h>
typedef struct student_s{
    int id;
    char name[30];
    float score;
}student_t;
int main (int argc,char *argv[]){
    // ./0_07homework file1
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    student_t stu[3]={{1,"zhangsan",66},
                        {2,"lisi",77},
                        {3,"wanglaowu",88}
    };
    ssize_t sret=write(fd,stu,sizeof(stu));
    student_t copy_stu[3];
    lseek(fd,0,SEEK_SET);
    read(fd,copy_stu,sizeof(stu));
    for(int i=0;i<sizeof(copy_stu)/sizeof(copy_stu[0]);i++){
        printf("id=%d name=%s score=%f\n",copy_stu[i].id,copy_stu[i].name,copy_stu[i].score);
    }
    return 0;
}
