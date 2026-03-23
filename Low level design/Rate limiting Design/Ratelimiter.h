#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>
#include <IRateLimiter.h>

class RateLimitar : public IRateLimitar
{
    private:
    struct TokenBucket
    {
        int capacity;
        double tokens;
        double refillRate;
        std::chrono::steady_clock::time_point lastRefillTime;
        std::mutex mtx;

        TokenBucket(int cap, double rate): capacity(cap), tokens(cap), refillRate(rate),
        lastRefillTime(std::chrono::steady_clock::now()){}
    };

    std::unordered_map<std::string, TokenBucket> buckets;
    std::mutex bucketMutex;

    public:
    RateLimitar(int cap, double rate);
    RateLimitar(const RateLimitar& other);
    RateLimitar& operator=(const RateLimitar& other);

    ~RateLimitar();

    bool allowrequest(const std::string key) override;
    double getRemainingQuotaofTokens(const std::string key) override;
    void reset(const std::string& key);

    private:
    std::shared_ptr<TokenBucket> getOrCreateBucket(const std::string& key);
    void refill(const std::shared_ptr<TokenBucket>& bucket);

};
