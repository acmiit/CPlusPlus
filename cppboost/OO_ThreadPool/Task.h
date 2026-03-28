#ifndef __TASK_H__
#define __TASK_H__

class Task{
public:
    Task();
    virtual ~Task();
    virtual void process()=0;
private:
};
#endif //__TASK_H__