#include<iostream>
#include<chrono>
using namespace std;

class Coupon
{
    string couponId;
    double discount;
    time_t expiry_time;
    int usesCount;

    public:
    Coupon(string id, double dis, time_t etime, int count): couponId(id), discount(dis), expiry_time(etime), usesCount(count){}

    bool bIsCouponValid()
    {
        if(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) < expiry_time && usesCount > 0)
            return true;

        return false;
    }

    double ApplyDiscount(int unitPrice)
    {
        if(!bIsCouponValid())
            throw std::runtime_error("invalid coupon.");

        return unitPrice - ((discount / 100) * unitPrice);
    }
};