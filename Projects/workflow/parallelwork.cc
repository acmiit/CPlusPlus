#include <54func.h>
#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
using std::cout;
using std::endl;
using std::string;
static WFFacilities::WaitGroup gWaitGroup(1);

struct SeriesContext{
    string url;
    size_t size;
};
void handler(int signum)
{
    cout << "signum=" << signum << endl;
    gWaitGroup.done(); // 计数器减一
}
void httpCallback(WFHttpTask * httpTask){
    cout<<"http callback\n";
    protocol::HttpResponse *resp=httpTask->get_resp();
    cout<<resp->get_http_version()<<" "<<resp->get_status_code()<<" "<<resp->get_reason_phrase()<<"\n";
    const void *body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    cout<<"size:"<<size<<"\n";
    SeriesContext * context=(SeriesContext *)series_of(httpTask)->get_context();
    context->size=size;
}
void parallelCallback(const ParallelWork * parallel){
    cout<<"parallel callback\n";
    for(size_t i=0;i<parallel->size();++i){
        SeriesContext * context=(SeriesContext *)parallel->series_at(i)->get_context();
        cout<<"url = "<<context->url<<"size = "<<context->size<<"\n";
        delete context;
    }
}
int main()
{
    signal(SIGINT, handler);
    std::vector<string> vec{
        "http://www.qq.com",
        "http://www.baidu.com",
        "http://www.taobao.com"
    };
    ParallelWork *parallel = Workflow::create_parallel_work(parallelCallback);
    for (int i=0;i<3;i++)
    {   
        WFHttpTask * httpTask=WFTaskFactory::create_http_task(vec[i],10,0,httpCallback);
        SeriesWork *Series=Workflow::create_series_work(httpTask,nullptr);
        SeriesContext * context=new SeriesContext;
        Series->set_context(context);
        context->url=vec[i];
        parallel->add_series(Series);
    }
    parallel->start();
    gWaitGroup.wait();
}