#include "timer.h"

namespace sylar {

bool Timer::cancel() 
{
    //读写锁，写锁
    //确保在取消timer时，其他线程不会修改timer的状态
    std::unique_lock<std::shared_mutex> write_lock(m_manager->m_mutex);

    if(m_cb == nullptr) 
    {
        return false; //已经被取消或者已经超时执行过了
    }
    else
    {
        m_cb = nullptr; //清理回调（不再使用）标记为无效
    }
    
    //从堆中移除
    auto it = m_manager->m_timers.find(shared_from_this());
    if(it!=m_manager->m_timers.end())
    {
        m_manager->m_timers.erase(it);
    }
    return true;
}

// refresh 只会向后调整
bool Timer::refresh() 
{
    //读写锁，写锁
    //确保在刷新timer时，其他线程不会修改timer的状态
    std::unique_lock<std::shared_mutex> write_lock(m_manager->m_mutex);

    if(!m_cb) 
    {
        return false; //已经被取消
    }

    auto it = m_manager->m_timers.find(shared_from_this());
    if(it==m_manager->m_timers.end())
    {
        return false; //不在堆中
    }
    
    //从堆中移除
    m_manager->m_timers.erase(it);
    //重新计算超时时间，从现在开始计算
    m_next = std::chrono::system_clock::now() + std::chrono::milliseconds(m_ms);
    //重新插入堆
    m_manager->m_timers.insert(shared_from_this());
    return true;
}

bool Timer::reset(uint64_t ms, bool from_now) 
{
    //如果参数没有改变且不从现在开始，直接返回成功
    if(ms==m_ms && !from_now)
    {
        return true;
    }

    {
        //读写锁，写锁
        //确保在重置timer时，其他线程不会修改timer的状态
        std::unique_lock<std::shared_mutex> write_lock(m_manager->m_mutex);
    
        if(!m_cb) 
        {
            return false; //已经被取消
        }
        
        auto it = m_manager->m_timers.find(shared_from_this());
        if(it==m_manager->m_timers.end())
        {
            return false; //不在堆中
        }   
        m_manager->m_timers.erase(it); //从堆中移除
    }

    // 计算新的起始时间，根据是否从现在开始计算，还是从上一个超时时间计算偏移
    auto start = from_now ? std::chrono::system_clock::now() : m_next - std::chrono::milliseconds(m_ms);
    m_ms = ms; //更新相对时间
    m_next = start + std::chrono::milliseconds(m_ms);//计算绝对时间

    //重新添加到堆中
    m_manager->addTimer(shared_from_this()); 
    return true;
}

Timer::Timer(uint64_t ms, std::function<void()> cb, bool recurring, TimerManager* manager)
:m_recurring(recurring), m_ms(ms), m_cb(cb), m_manager(manager) 
{
    //计算绝对超时时间
    auto now = std::chrono::system_clock::now();
    m_next = now + std::chrono::milliseconds(m_ms);
}
//最小堆比较器
bool Timer::Comparator::operator()(const std::shared_ptr<Timer>& lhs, const std::shared_ptr<Timer>& rhs) const
{
    assert(lhs!=nullptr&&rhs!=nullptr);
    return lhs->m_next < rhs->m_next;
}

TimerManager::TimerManager() 
{
    m_previouseTime = std::chrono::system_clock::now();
}

TimerManager::~TimerManager() 
{
}

std::shared_ptr<Timer> TimerManager::addTimer(uint64_t ms, std::function<void()> cb, bool recurring) 
{
    std::shared_ptr<Timer> timer(new Timer(ms, cb, recurring, this));
    addTimer(timer);
    return timer;
}

// 如果条件存在 -> 执行cb()
static void OnTimer(std::weak_ptr<void> weak_cond, std::function<void()> cb)
{
    //尝试提升weak_ptr为shared_ptr 
    std::shared_ptr<void> tmp = weak_cond.lock();
    if(tmp)
    {
        cb(); //对象还活着，执行回调
    }
    //对象已经销毁，什么都不做
}

std::shared_ptr<Timer> TimerManager::addConditionTimer(uint64_t ms, std::function<void()> cb, std::weak_ptr<void> weak_cond, bool recurring) 
{
    return addTimer(ms, std::bind(&OnTimer, weak_cond, cb), recurring);
}

uint64_t TimerManager::getNextTimer()
{
    //读写锁，读锁
    std::shared_lock<std::shared_mutex> read_lock(m_mutex);
    
    // 重置tickle标志位，允许下次添加timer时再次通知
    m_tickled = false;
    
    if (m_timers.empty())
    {
        // 返回unsigned long的最大值，表示"无限远"
        return ~0ull;
    }

    auto now = std::chrono::system_clock::now();
    auto time = (*m_timers.begin())->m_next; //堆顶 = 最早超时的timer

    if(now>=time)
    {
        // 已经有timer超时
        return 0;
    }
    else
    {
        //计算距离超时的毫秒数
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time - now);
        return static_cast<uint64_t>(duration.count());            
    }  
}

void TimerManager::listExpiredCb(std::vector<std::function<void()>>& cbs)
{
    auto now = std::chrono::system_clock::now();

    //读写锁，写锁
    std::unique_lock<std::shared_mutex> write_lock(m_mutex); 
    //检测系统时间是否回退
    bool rollover = detectClockRollover();
    
    //循环处理所有超时timer
    //条件：堆非空 && 系统时间 >= 堆顶timer的超时时间 || 系统时间回退
    while (!m_timers.empty() && rollover || !m_timers.empty() && (*m_timers.begin())->m_next <= now)
    {
        std::shared_ptr<Timer> temp = *m_timers.begin();
        m_timers.erase(m_timers.begin()); //从堆中移除
        
        cbs.push_back(temp->m_cb); //收集回调函数

        if (temp->m_recurring)
        {
            //循环timer：重新计算下次触发时间并插入堆
            temp->m_next = now + std::chrono::milliseconds(temp->m_ms);
            m_timers.insert(temp);
        }
        else
        {
            //非循环timer：清理回调（不再使用）
            temp->m_cb = nullptr;
        }
    }
}

bool TimerManager::hasTimer() 
{
    std::shared_lock<std::shared_mutex> read_lock(m_mutex);
    return !m_timers.empty();
}

// lock + tickle()，内部接口，用于添加timer到时间堆中
void TimerManager::addTimer(std::shared_ptr<Timer> timer)
{
    bool at_front = false;
    {
        std::unique_lock<std::shared_mutex> write_lock(m_mutex);
        //插入到set中，返回迭代器
        auto it = m_timers.insert(timer).first;
        //判断是否成为新的堆顶
        //注意：是新的最早超时的timer，且还没有被tickle过
        at_front = (it == m_timers.begin()) && !m_tickled;
        
        
        if(at_front)
        {
            m_tickled = true; //标记已经tickle，防止重复通知
        }
    }
   //如果是新的堆顶，需要通知（唤醒epoll等待）
    if(at_front)
    {
        onTimerInsertedAtFront();
    }
}

bool TimerManager::detectClockRollover() 
{
    bool rollover = false;
    auto now = std::chrono::system_clock::now();
    //如果当前时间回退了60分钟，认为是系统时间回退
    if(now < (m_previouseTime - std::chrono::milliseconds(60 * 60 * 1000))) 
    {
        rollover = true;
    }
    m_previouseTime = now;
    return rollover;
}

}

