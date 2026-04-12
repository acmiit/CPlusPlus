#include <54func.h>
#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
using std::cerr;
using std::cout;
using std::endl;
using std::string;
static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum)
{
    cout << "signum=" << signum << endl;
    gWaitGroup.done(); // 计数器减一
}
// 上下文context
struct ChainContext
{
    string last_valid_value; // 记录上一次成功查到的非空值
};
void redis_callback(WFRedisTask *task)
{
    int state = task->get_state();
    int error = task->get_error();
    if (state != WFT_STATE_SUCCESS)
    {
        cerr << "Redis 任务失败！ State: " << state << "Error: " << error << endl;
        gWaitGroup.done();
        return;
    }
    protocol::RedisResponse *resp = task->get_resp();
    protocol::RedisValue val;
    resp->get_result(val);

    //获取当前序列以及绑定的上下文
    SeriesWork *series = series_of(task);
    ChainContext *ctx = static_cast<ChainContext *>(series->get_context());
    if (val.is_nil())
    {
        if (ctx->last_valid_value.empty())
        {
            cout << "查询中止：初始 Key 就不存在！" << endl;
        }
        else
        {
            // 如果上一个值存在，但拿它去查却查不到东西，说明上一个值就是终点！
            cout << "\n链条已到底！最终的值是: [" << ctx->last_valid_value << "]" << endl;
        }
        gWaitGroup.done();
        return;
    }
    if(val.is_string()){
        string current_val=val.string_value();
        cout<<"查到节点： "<<current_val<<"继续向下查询……"<<endl;
        //更新上下文
        ctx->last_valid_value=current_val;
        //递归查询
        WFRedisTask * next_task=WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redis_callback);
        next_task->get_req()->set_request("GET",{current_val});
        // 将新任务追加到序列末尾
        series->push_back(next_task);  
    } else {
        cerr << "遇到非字符串类型的值，探测中止。" << endl;
        gWaitGroup.done();
    }
}
int main()
{
    signal(SIGINT, handler);

    // 利用工厂函数创建一个任务
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 2, redis_callback);

    // 设置httpTask的属性 请求
    protocol::RedisRequest *req = redisTask->get_req();
    req->set_request("get", {"x1"});
    //手动创建 SeriesWork，以便我们可以设置 Context 和销毁回调
    SeriesWork *series = Workflow::create_series_work(redisTask, [](const SeriesWork *series) {
        // 当整个序列（包含所有动态追加的任务）全部执行完毕时，会进入这个回调
        // 我们需要在这里清理手动 new 出来的 Context，防止内存泄漏
        ChainContext *ctx = static_cast<ChainContext *>(series->get_context());
        delete ctx;
        cout << "序列执行完毕，Context 资源已回收。" << endl;
    });
    ChainContext *ctx = new ChainContext();
    ctx->last_valid_value = ""; 
    series->set_context(ctx);
    // 启动 交给框架来做
    series->start();
    gWaitGroup.wait();
}