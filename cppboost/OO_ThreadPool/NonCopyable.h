#ifndef __NONCOPYABLE__H__
#define __NONCOPYABLE__H__
//静止复制
class NonCopyable{
protected:
    NonCopyable()=default;
    NonCopyable(const NonCopyable &rhs)=delete;
    NonCopyable& operator=(const NonCopyable &rhs)=delete;
};

#endif //__NONCOPYABLE__H__