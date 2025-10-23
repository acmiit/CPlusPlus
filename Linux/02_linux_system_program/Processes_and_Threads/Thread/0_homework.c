#include<54func.h>
typedef struct node{
    int data;
    struct node * next;
}node,*Pnode;
void headInsert(Pnode *L,int data){
    Pnode t = (Pnode)malloc(sizeof(node));
    memset(t,0,sizeof(node));
    t->data=data;
    t->next=(*L)->next;
    (*L)->next=t;
}
void *threadFunc(void *arg){
    Pnode L=(Pnode)arg;
    while(L !=NULL){
        printf("%d ",L->data);
        L=L->next;
    }
    printf("\n");
    return NULL;
}
int main(){
    Pnode L = (Pnode)malloc(sizeof(node));
    L->next=NULL;
    L->data=1;
    headInsert(&L,4);
    headInsert(&L,3);
    headInsert(&L,2);
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,L);
    sleep(1);
    return 0;
}