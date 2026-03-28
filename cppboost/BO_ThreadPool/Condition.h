#ifndef __CONDITION_H__
#define __CONDITION_H__
#include <pthread.h>
// #include"MutexLock.h" 能用class MutexLock前向声明就不要使用头文件，防止头文件相互引用造成死循环
class MutexLock;
class Condition
{
public:
    Condition(MutexLock & mutex);
    ~Condition();
    //睡眠
    void wait();
    //通知
    void notify();
    void notifyALL();
private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};

#endif //__CONDITION_H__