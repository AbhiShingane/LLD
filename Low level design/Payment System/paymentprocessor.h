#include<iostream>
#include<paymentrequest.h>
#include<transaction.h>
#include<idempotencykey.h>
#include<paymentadapter.h>

using namespace std;

//The IPaymentProcessor interface defines the contract for processing payments. It has a pure virtual function processPayment that takes a PaymentRequest object as input. This allows for different payment processing strategies to be implemented for different payment methods, while adhering to the same interface.
class IPaymentProcessor {
      IdempotencyKey idempotencyKey;
      IPaymentGateway* paymentGateway;
    
    public:
        virtual transaction InitiatePayment(PaymentRequest request) = 0;
        virtual void processPayment(transaction txn) = 0;
        virtual void retryPayment(transaction txn) = 0;
};


//enum for different UPI providers and banks is defined to handle specific payment processing logic for each provider or bank. This allows for more granular control over the payment processing flow based on the selected provider or bank.
enum UPIProvider {
    PAYTM,
    PHONEPE,
    GOOGLE_PAY
};

enum Bank {
    HDFC,
    ICICI,
    SBI
};


//Here the strategy pattern is used to implement different payment processing strategies for different payment methods. Each payment method has its own implementation of the processPayment function, which is defined in the IPaymentProcessor interface. This allows for easy extension of the payment processing system by adding new payment methods without modifying existing code.
class CardPaymentProcessor : public IPaymentProcessor {
        string currentIdempotencyKey;
    public:
        CardPaymentProcessor(IpaymentGateway* gateway) {
            paymentGateway = gateway;
        }
        transaction InitiatePayment(PaymentRequest request) override {
            if (idempotencyKey.isDuplicate(request.getIdempotencyKey())) {
                throw invalid_argument("Duplicate payment request");
            }
            currentIdempotencyKey = request.getIdempotencyKey();
            return transaction("txn_" + request.getPaymentId(), request.getPaymentId(), request.getAmount(), INITIATED);
        }

        void processPayment(transaction txn) override {
            cout << "Processing card payment of amount: " << txn.getAmount() << endl;
            // Implement card payment processing logic here
            int count = 3;
            while(count --)
            {
                auto paymentResponse =  gateway->pay(PaymentRequest(txn.getPaymentId(), txn.getAmount(), CARD, {}, ""));

                if (paymentResponse->getStatus() == SUCEESS) {
                    txnst.setStatus(COMPLETED);
                } else {
                    txnst.setStatus(FAILED);
                }

                if(txnst.getStatus() == COMPLETED) {
                    break;
                }
            }

            idempotencyKey.storeKey(currentIdempotencyKey);
        }
};


class NetBankingPaymentProcessor : public IPaymentProcessor {
    public:
        transaction InitiatePayment(PaymentRequest request) override {
            if (idempotencyKey.isDuplicate(request.getIdempotencyKey())) {
                throw invalid_argument("Duplicate payment request");
            }
            currentIdempotencyKey = request.getIdempotencyKey();
            return transaction("txn_" + request.getPaymentId(), request.getPaymentId(), request.getAmount(), INITIATED);
        }

        void processPayment(transaction txn) override {
            cout << "Processing net banking payment of amount: " << txn.getAmount() << endl;
            // Implement net banking payment processing logic here
            int count = 3;
            while(count --)
            {
                auto paymentResponse =  gateway->pay(PaymentRequest(txn.getPaymentId(), txn.getAmount(), NET_BANKING, {}, ""));

                if (paymentResponse->getStatus() == SUCEESS) {
                    txnst.setStatus(COMPLETED);
                } else {
                    txnst.setStatus(FAILED);
                }

                if(txnst.getStatus() == COMPLETED) {
                    break;
                }
            }

            idempotencyKey.storeKey(currentIdempotencyKey);
        }
};

class UPIPaymentProcessor : public IPaymentProcessor {
    public:
        transaction InitiatePayment(PaymentRequest request) override {
            if (idempotencyKey.isDuplicate(request.getIdempotencyKey())) {
                throw invalid_argument("Duplicate payment request");
            }
            currentIdempotencyKey = request.getIdempotencyKey();
            return transaction("txn_" + request.getPaymentId(), request.getPaymentId(), request.getAmount(), INITIATED);
        }

        void processPayment(transaction txn) override {
            cout << "Processing UPI payment of amount: " << txn.getAmount() << endl;
            // Implement UPI payment processing logic here
            int count = 3;
            while(count --)
            {
                auto paymentResponse =  gateway->pay(PaymentRequest(txn.getPaymentId(), txn.getAmount(), UPI, {}, ""));

                if (paymentResponse->getStatus() == SUCEESS) {
                    txnst.setStatus(COMPLETED);
                } else {
                    txnst.setStatus(FAILED);
                }

                if(txnst.getStatus() == COMPLETED) {
                    break;
                }
            }

            idempotencyKey.storeKey(currentIdempotencyKey);
        }