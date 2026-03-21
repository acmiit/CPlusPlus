#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;
class LRUCache
{
public:
    LRUCache(int capacity)
        : _capacity(capacity)
    {
    }

    int get(int key)
    {
        auto it = _hashMap.find(key);
        if (it == _hashMap.end())
        {
            cout<<"-1"<<endl;
            return -1;
        }
        _cache.splice(_cache.begin(), _cache, it->second);
        cout<<it->second->second<<endl;
        return it->second->second;
    }
    void put(int key, int value)
    {
        auto it = _hashMap.find(key);
        if (it != _hashMap.end())
        {
            it->second->second = value;
            _cache.splice(_cache.begin(), _cache, it->second);
            return;
        }
        if (_cache.size() == _capacity)
        {
            int keyToDelete = _cache.back().first;
            _hashMap.erase(keyToDelete);
            _cache.pop_back();
        }
        _cache.push_front({key, value});
        _hashMap[key] = _cache.begin();
    }
private:
    list<pair<int, int>> _cache;
    unordered_map<int, list<pair<int, int>>::iterator> _hashMap;
    int _capacity;
};
int main()
{
    LRUCache l(2);
    l.put(1, 1);
    l.put(2, 2);
    l.get(1);
    l.put(3, 3);
    l.get(2);
    l.put(4, 4);
    l.get(1);
    l.get(3);
    l.get(4);
    return 0;
}