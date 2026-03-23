#include<iostream>
using namespace std;
template<class T>
class Vector{
public:
    Vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_end_of_storage(null)
    {

    }
    ~Vector(){

    }
    void push_back(const T &value){
        if(size()==capacity()){
            reallocate(); //进行扩容
        }else{
            _alloc.construct(_finish++,value);
        }
    }
    void pop_back(){
        if(size()>0){
            _alloc.destroy(--_finish);
        }
    }
    void size(){
        return _finish-_start;
    }
    void capacity(){
        return _end_of_storage-_start;
    }
private:
    void reallocate() //重新分配内存，动态扩容要用的
    {
        int oldcapacity=capacity();
        int newcapacity=2*oldcapacity>0?2*oldcapacity:1; //新空间扩容的大小，申请空间
        T * newpoint=_alloc.allocate(newcapacity);  //创建对象
        if(_start){
            copy(_start,_finish,newpoint);
            while(_finish!=_start){
                _alloc.destroy(--_finish);  //删除对象
            }
            _alloc.deallocate(_start,capacity());//释放空间
            _start=newpoint;
            _finish=_start+oldcapacity;
            _end_of_storage=_start+newcapacity;
        }
    }
private:
    static allocator<T> _alloc;
    T * _start;
    T * _finish;
    T * _end_of_storage;
};
template<class T>
allocator<T> Vector<T>::_alloc;
void test(){

}
int main(){
    return 0;
}