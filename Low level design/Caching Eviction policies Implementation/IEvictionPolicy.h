#include<iostream>
#include<string>

template <typename K, typename V>
class IEvictionPolicy
{
    virtual void OnGet(const K& key)  = 0;
    virtual void OnPut(const k& key, const V& val) = 0;
    virtual void onDelete() = 0;

    virtual ~IEvictionPolicy() = delete;
};