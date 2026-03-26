#include <pthread.h>
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
class MutexLock
{
public:
    MutexLock();
    ~MutexLock();
    //上锁
    void lock();
    //解锁
    void unlock();
    // 尝试上锁
    void trylock();
    //获取数据成员
    pthread_mutex_t * getMutexLockPtr();
private:
    pthread_mutex_t _mutex;
};

#endif //__MUTEXLOCK_H__