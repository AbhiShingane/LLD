#include<iostream>
#include<IEvictionPolicy.h>
#include<vector>
#include<queue>
#include<algorithm>

template <typename K, typename V>
class FIFOEvictionPolicy: public IEvictionPolicy<K, V>
{
    std::vector<K> que;
    std::map<K, V> store;
    int maxSize = 0;
    std::map<K, std::queue<pair<K, V>>::iterator> addr;


    public:
    FIFOEvictionPolicy(int sz) : maxSize(sz){}

    void OnGet(const K& key)  override
    {
        // Doesn't care about the access.
    }

    void OnPut(const k& key, const V& val) override
    {
        if(store.find(key))
        {
            return;
        }

        if(store.size() == maxSize)
        {
            auto itemkey = que.back();
            que.pop_back();
            auto posn = addr[itemkey];
            addr.erase(itemkey);
            store.erase(itemkey);
        }

        store[key] = val;
        que.push_front(key);
        addr[key] = que.begin();

    }

    void onDelete() override
    {
        auto key = que.back();
        que.pop_back();
        store.erase(key);
        auto pos = addr[key];
        addr.erase(key);
    }

    ~FIFOEvictionPolicy()
    {

    }
};