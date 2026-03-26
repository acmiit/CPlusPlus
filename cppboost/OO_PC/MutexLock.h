
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include "NonCopyable.h"
#include <pthread.h>
class MutexLock
    : NonCopyable
{
public:
    MutexLock();
    ~MutexLock();
    // MutexLock(const MutexLock & rhs)=delete;
    // MutexLock& operator=(const MutexLock &rhs)=delete;
    // 上锁
    void lock();
    // 解锁
    void unlock();
    // 尝试上锁
    void trylock();
    // 获取数据成员
    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;
};
class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
        : _mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};
#endif //__MUTEXLOCK_H__