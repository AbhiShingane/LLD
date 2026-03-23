#include <iostream>
#include <Ratelimiter.h>

using nammespace std;

RateLimitar::RateLimitar(int cap, double rate)
{
    capacity = cap;
    refillRate = rate;
}

RateLimitar::RateLimitar(const RateLimitar& other){
    //Implementation of copy constructor
}

RateLimitar& RateLimitar::operator=(const RateLimitar& other){
    //Implementation of assignment operator
}

bool RateLimitar::allowrequest(const std::string key) override
{
    auto bucket = getOrCreateBucket(key);

    std::lock_guard<std::mutex> lock(bucket->mtx);

    refill(bucket);

    if(bucket.tokens >= 1)
    {
        bucket.tokens -= 1;
        return true;
    }

    return false;
}

double RateLimitar::getRemainingQuotaofTokens(const std::string key) override
{
    auto bucket = getOrCreateBucket(key);

    std::lock_gurad<std::mutex> lock(bucket->mtx);

    refill(bucket);

    return bucket->tokens;
}

// This will reset the bucket storage by removing the respective key from it.
void RateLimitar::reset(const std::string& key) override
{
    std::lock_guard<std::mutex> lock(bucketMutex);

    buckets->erase(key);
}


std::shared_ptr<TokenBucket> RateLimitar::getOrCreateBucket(const std::string& key)
{
    std::lock_guard<std::mutex> lock(bucketMutex);

    if(buckets.find(key) == bucket.end())
    {
        buckets[key] = std::make_shared<TokenBucket>(capacity, refillRate);
    }

    return buckets[key];
}


void RateLimitar::refill(const std::shared_ptr<TokenBucket>& bucket)
{
    auto now = std::chrono::steady_clock::now();

    double elapsed = std::chrono::duration<double>(now - bucket->lastRefillTime);

    double tokenstoadd = elapsed * bucket->refillRate;

    bucket->tokens = std::min(std::static_cast<double> capacity, tokenstoAdd);

    bucket->lastRefillTime = now;

    return;
}