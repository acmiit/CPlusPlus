#include "thread.h"
#include <sys/syscall.h> 
#include <iostream>
#include <unistd.h>  

namespace sylar {

// 线程信息
static thread_local Thread* t_thread          = nullptr;
static thread_local std::string t_thread_name = "UNKNOWN";

pid_t Thread::GetThreadId() //获取系统分配的线程id
{
	return syscall(SYS_gettid); //syscall(SYS_gettid)是一个系统调用，用于获取当前线程的唯一ID。SYS_gettid 是 Linux 特定的系统调用编号，用来获取线程ID (TID)。pid_t 是一个数据类型，用于表示进程ID或线程ID。
}

Thread* Thread::GetThis() //获取当前所在线程
{
    return t_thread;
}

const std::string& Thread::GetName() //获取当前线程的名字
{
    return t_thread_name;
}

void Thread::SetName(const std::string &name) //设置当前线程的名字
{
    if (t_thread) 
    {
        t_thread->m_name = name;
    }
    t_thread_name = name;
}

Thread::Thread(std::function<void()> cb, const std::string &name): 
m_cb(cb), m_name(name) 
{
    //·创建线程：调用pthread_create()创建线程，将cb函数作为线程的入口函数，将this作为参数传递给cb函数
    //这是需要注意的是this是传递给run函数进行转换的
    //目的就是将cb函数作为线程的入口函数，将this作为参数传递给cb函数
    //int pthread_create(pthread_t *thread,  线程标识符
                //    const pthread_attr_t *attr,   线程属性
                //    void *(*start_routine) (void *), 线程入口函数
                //    void *arg); // 线程入口函数的参数
    //返回值：0 成功，其他值 失败
    //错误码：EAGAIN 线程创建失败，资源不足
    //         EBUSY 线程创建失败，线程池已满
    //         EINVAL 线程属性无效
    //         ENOMEM 线程创建失败，内存不足
    int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);    //这是需要注意的是this是传递给run函数进行转换的
    if (rt) 
    {
        std::cerr << "pthread_create thread fail, rt=" << rt << " name=" << name;
        throw std::logic_error("pthread_create error");
    }
    // 等待线程函数完成初始化
    m_semaphore.wait();
}

Thread::~Thread() 
{
    if (m_thread) 
    {
        pthread_detach(m_thread);
        m_thread = 0;
    }
}

void Thread::join() 
{
    if (m_thread) 
    {
        int rt = pthread_join(m_thread, nullptr);
        if (rt) 
        {
            std::cerr << "pthread_join failed, rt = " << rt << ", name = " << m_name << std::endl;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }
}

void* Thread::run(void* arg) 
{
    Thread* thread = (Thread*)arg;

    //全局静态变量
    t_thread       = thread; 
    t_thread_name  = thread->m_name;
    thread->m_id   = GetThreadId();
    //pthread_self()获取当前线程的id，设置m_name是前15个字节取，
    //目的就是设置线程的名字方便调试，方便查看线程信息
    //存在可能问的问题：为什么是0，15
    //由于操作系统对线程名称长度的限制决定的
    //Linux中线程最大的名字只能是15，后面还有一个\0总共16.
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str()); //给线程取别名

    std::function<void()> cb;
    cb.swap(thread->m_cb); // swap -> 可以减少m_cb中只能指针的引用计数
    
    // 初始化完成
    thread->m_semaphore.signal();

    cb();   //真正执行的函数
    return 0;
}

} 

