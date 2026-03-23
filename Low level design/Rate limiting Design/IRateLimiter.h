#include <iostream>
#include <string>

class IRateLimitar
{
    virtual bool allowrequest(const std::string key) = 0;
    virtual double getRemainingQuotaofTokens(const std::string key) = 0;
    virtual void reset(const std::string& key) = 0;
};