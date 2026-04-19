#include<iostream>
#include<IEvictionPolicy.h>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

template <typename K, typename V>
class LRUEvictionPolicy : public IEvictionPolicy<K, V>
{
    int maxSize;
    std::vector<K> que;
    std::unordered_map<K, V> store;
    std::unordered_map<K, std::unordered_map<K,V>::iterator> addr;

    public:
    LRUEvictionPolicy(int sz):maxSize(sz){}

    void OnGet(const K& key) override
    {
        if(!addr.count(key))
            return;

        return addr[key];
    }

    void OnPut(const K& key, const V& val) override
    {
        if(store.count(key))
        {
            auto posn = addr[key];
            que.erase(posn);
            addr.erase(key);
            que.push_front(key);
            addr[key] = q.begin();
        }

        if(store.size() == maxSize)
        {
            auto itemkey = que.back();
            que.pop_back();
            //store.erase(itemkey);
            addr.erase(itemkey);
        }

        //store[key] = val;
        que.push_front(key);
        addr[key] = que.begin();
    }

    void onDelete()
    {
        int itemkey = que.back();
        que.pop_back();
        store.erase(itemkey);
        addr.erase(itemkey);

        return;
    }

};