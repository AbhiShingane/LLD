#include<iostream>
#include<IRateLimiter.h>
#include<mutex>
#include<queue>
#include<unordered_map>
#include<vector>

using namespace std;

class LeakyBucketStrategy: public IRateLimitar
{
    private:
    struct LeakyBucket
    {
        int capacity;
        int outflowrate;
        std::chrono::steady_clock::time_point lastprocessedtime;
        mutex mtx;

        queue<int> que;
        
        LeakyBucket(int cap, int outrate) : capacity(cap), outflowrate(outrate), lastprocessedtime(std::chrono::steady_clock::now()){}
    };

    unordered_map<string, shared_ptr<LeakyBucket>> store;
    std::mutex bucketmutex;
    int _capacity;
    int _outrate;

    std::shared_ptr<LeakyBucket> getorCreateBucket(const string& key)
    {
        std::lock_guard<mutex> lock(bucketmutex);
        if(store.find(key) == store.end())
        {
            store[key] = make_shared<LeakyBucket>(_capacity, _outrate);
        }

        return store[key];
    }

    public:
    LeakyBucketStrategy(int cap, int outflow) : _capacity(cap), _outrate(outflow){}
    //copy constructor
    //copy assignement operator
    bool allowrequest(const std::string key) override
    {
        auto bucket = getorCreateBucket(key);

        std::lock_guard<mutex> lock(bucket->mtx);

        if(bucket->que.size() == bucket->capacity)
            return false;

        bucket->que.size() -= bucket->outflowrate;

        return true;
    }

    double getRemainingQuotaofTokens(const std::string key)
    {
        auto bucket = getorCreateBucket(key);

        std::lock_guard<mutex> lock(bucket->mtx);

        return std::max(0, bucket->capacity - bucket->que.size());
    }

    void reset(const std::string& key)
    {
        std::lock_guard<mutex> lock(bucketmutex);

        store.erase(key);
    }
};