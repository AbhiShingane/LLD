#include<iostream>
#include<IRateLimiter.h>
#include<chrono>
#include<mutex>
#include<map>
#include<unordered_map>
using namespace std;

class TokenBucketStrategy : public IRateLimitar
{
    private:
    struct TokenBucket
    {
        public:
        int capacity;
        int refillrate;
        std::chrono::steady_clock::time_point lastrefillTime;
        double tokens;
        std::mutex mtx;

        TokenBucket(int cap, int refill): capacity(cap), refillrate(refill), lastrefillTime(std::chrono::steady_clock::now()){}
    };
    
    unordered_map<string, std::shared_ptr<TokenBucket>> store;
    std::mutex bucketmutex;
    int capacity_;
    int refillrate_;

    shared_ptr<TokenBucket> getorCreateBucket(const string& key)
    {
        std::lock_guard<mutex> lock(bucketmutex);

        if(store.find(key) == store.end())
        {
            store[key] = make_shared<TokenBucket>(capacity_, refillrate_);
        }

        return store[key];
    }

    void refill(std::shared_ptr<TokenBucket> bucket)
    {
        auto now = std::chrono::steady_clock::now();

        double  elapsed = std::chorno::duration<double>(bucket->lastrefillTime - now);

        int numberofTokens  = elapsed * refillrate_;

        bucket->tokens = std::min(bucket->capacity, numberofTokens);

        bucket->lastrefillTime = now;
    } 

    public: 
    
    TokenBucketStrategy(int cap, int refill)
    {
        capacity_ = cap;
        refillrate_ = refill;
    }

    bool allowrequest(const std::string key) override
    {
        auto bucket = getorCreateBucket(key);

        std::lock_guard<std::mutex> lock(bucket->mtx);

        refill(bucket);

        if(bucket->tokens >= 1)
        {
            bucket->tokens -= 1;
            return true;
        }

        return false;

    }

    double getRemainingQuotaofTokens(const std::string key) override
    {
        auto bucket = getorCreateBucket(key);

        std::lock_guard<std::mutex> lock(bucket->mtx);

        refill(bucket);

        return bucket->tokens;
    }

    void reset(const std::string& key) override
    {
        std::lock_guard<std::mutex> lock(bucketmutex);

        store.erase(key);
    }
};