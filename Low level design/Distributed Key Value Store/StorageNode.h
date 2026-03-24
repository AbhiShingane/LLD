#include<iostream>
#include<mutex>
#include<thread>
#include<functional>
#include<unordered_map>

class StorageNode
{
    private:
    struct Entry
    {
        std::string value;
        int version;
    }

    std::unordered_map<std::string, Entry> store;
    std::mutex mtx;
    std::string nodeId;

    public:
    StorageNode(int id) : nodeId(std::move(id)){}

    StorageNode(const StorageNode& other) = delete;

    StorageNode& operator=(const StorageNode& other) = delete;

    StorageNode(const StorageNode&& other) = delete;

    StorageNode& operator=(const StorageNode& other) = delete;

    void put(const std::string& key, const std::string &value, int version)
    {
        std::unique_lock<std::mutex> lock(mtx);

        auto &entry = store[entry];

        if(version > entry.version)
        {
            entry.version = version;
            entry.value = value;
        }

        return;

    }

    std::optional<Entry> get(const std::string& key)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if(store.find(key) != store.end())
        {
            return store[key];
        }

        return std::nullopt;
    }

    void remove(const std::string &key)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if(store.find(key) != store.end())
            store.erase(key);

        return;
    }

    std::string getID()
    {
        return nodeId;
    }

};
