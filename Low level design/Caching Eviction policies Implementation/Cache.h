#include<iostream>
#include<IEvictionPolicy.h>
#include<LRUEvictionPolicy.h>
#include<FIFOEvictionPolicy.h>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

template <typename K, typename V>
class Cache
{
    unordered_map<K, V> store;
    size_t capacity;
    unique_ptr<IEvictionPolicy<K,V>> policy;

    public:
    Cache(size_t cap, unique_ptr<IEvictionPolicy<K,V>> p) : capacity(cap), policy(p){}
    
    void setPolicy(unique_ptr<IEvictionPolicy<K,V>> p)
    {
        policy = p;
    }

    std::optional<V> onGetItem(const K& key)
    {
        if(store.cont(key)) return nullptr;

        policy->OnGet(key);

        return store[key];
    }

    void PutItem(const K& key, const V& val)
    {
        //if()
    }

};