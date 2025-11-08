#include<54func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    struct hostent *entry=gethostbyname(argv[1]);
    if(entry == NULL){
        herror("gethostbyname");
        return -1;
    }
    printf("official name = %s\n",entry->h_name);
    for(int i=0;entry->h_aliases[i]!=NULL;i++){
        printf("\t alias=%s\n",entry->h_aliases[i]);
    }
    for(int i=0;entry->h_addr_list[i]!=NULL;i++){
        char ip[1024];
        inet_ntop(entry->h_addrtype,entry->h_addr_list[i],ip,1024);
        printf("ip = %s\n",ip);
    }
    return 0;
}