#include<iostream>
#include<vector>
#include<product.h>
#include<Order.h>
#include<OrderItem.h>

enum class PayStatus {PENDING, SUCCESS, FAILED, REFUND};

enum class PayMethod {UPI, CARD, COD};

class Payment
{
    std::string paymentId;
    std::string orderId;
    std::string userId;
    PayStatus paymentsts;
    PayMethod paymethod;
    double amount;

    public:
    payment(string payid, string oid, string uid, double amt)
    {
        paymentId = payid;
        orderId = oid;
        userId = uid;
        amount = amt;
    }

    void cancelPayment()
    {
        if(paymentSts == PaymentStatus::FAILED)
        {
            throw std::runtime_error("payment is already failed");
        }

        paymentSts = PaymentStatus::FAILED:
    }

    std::string getId()
    {
        return paymentId;
    }

    PaymentStatus getpayementStatus()
    {
        return paymentSts;
    }

    bool process()
    {
        //processing the payment by calling the payment gateway for the amount

        cout<<"payement processing "<<endl;
        paymentSts = PaymentStatus::SUCCESS;

        return true;
    }

    bool refund()
    {
        //change the status to payment refunded
        return true;
    }
}
