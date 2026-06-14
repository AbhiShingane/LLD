#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;


enum PaymentMethodType {
    CARD,
    NET_BANKING,
    UPI,
    WALLET
};

class PaymentRequest {
    private:
        string paymentId;
        double amount;
        PaymentMethodType paymentMethod;
        unordered_map<string, string> paymentDetails;
        string idempotencyKey;

    public:
        PaymentRequest(string id, double amt, PaymentMethodType method, unordered_map<string, string> details, string idempotencyKey) {
            paymentId = id;
            amount = amt;
            paymentMethod = method;
            paymentDetails = details;
            this->idempotencyKey = idempotencyKey;
        }

        string getPaymentId() {
            return paymentId;
        }

        double getAmount() {
            return amount;
        }

        string getIdempotencyKey() {
            return idempotencyKey;
        }

        PaymentRequest getPaymentRequest() {
            return *this;
        }

    
};


typedef enum
{
CANCELLED,
SUCEESS,
FAILED,
REFUNDED
}paymentstatustype;


class PaymentResponse {
    private:
        string paymentId;
        paymentstatustype status;
        string message;

    public:
        PaymentResponse(string id, paymentstatustype stat, string msg) {
            paymentId = id;
            status = stat;
            message = msg;
        }

        string getPaymentId() {
            return paymentId;
        }

        paymentstatustype getStatus() {
            return status;
        }

        string getMessage() {
            return message;
        }

        PaymentResponse getPaymentResponse() {
            return *this;
        }
};

class PaymentStatus {
    private:
        string paymentId;
        paymentstatustype status;

    public:
        PaymentStatus(string id, paymentstatustype stat) {
            paymentId = id;
            status = stat;
        }

        PaymentStatus getPaymentStatus() {
            return *this;
        }
};