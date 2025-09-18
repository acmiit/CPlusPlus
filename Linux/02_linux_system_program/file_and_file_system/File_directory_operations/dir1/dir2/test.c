#include<stdio.h>
void print(int arr[],int len){
    for(int i=0;i<len-1;i++)
        printf("%d ",arr[i]);
    printf("%d\n",arr[len-1]);
}
int main(){
    int arr[1024],len;
    int n;
    scanf("%d",&n);
    len=n;
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    print(arr,len);
    int e,insert;
    scanf("%d%d",&e,&insert);
    for(int i=n;i>insert-1;i--){
        arr[i]=arr[i-1];
    }
    len++;
    arr[insert-1]=e;
    print(arr,len);
    int delect;
    scanf("%d",&delect);
    e=arr[delect-1];
    for(int i=delect-1;i<len-1;i++)
        arr[i]=arr[i+1];
    len--;
    printf("%d\n",e);
    print(arr,len);
    return 0;
}