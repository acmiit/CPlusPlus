#include<iostream>
using namespace std;
union 
{
    uint32_t x;
    uint8_t c[4];
}u={0x12345678};



int main(){
    bool t=u.c[0]==0x78;
    int x=0x12345678;
    char *p=(char *)&x;
    int temp=(int)p[0];
    cout<<t<<endl;
    printf("0x%x\n",temp);
    return 0;
}