#include<iostream>
#include<string>
#include<map>
#include<paymentprocessor.h>
#include<paymentrequest.h>

using namespace std;



class IPaymentGateway
{
    public:

        virtual unique_ptr<PaymentResponse> pay(PaymentRequest request) = 0;
        virtual unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) = 0;
        virtual unique_ptr<PaymentResponse> cancelPayment(string paymentId) = 0;
        virtual unique_ptr<PaymentResponse> refundPayment(string paymentId) = 0;

};


// gateway adapter class to adapt the payment gateway to the payment processor interface
// UPI baed payment gateway adapter class to adapt the payment gateway to the payment processor interface
class gpaypaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        gpaypaymentGateway() {
            paymentProcessor = make_unique<UPIPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

class phonepepaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        phonepepaymentGateway() {
            paymentProcessor = make_unique<UPIPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

class credpaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        credpaymentGateway() {
            paymentProcessor = make_unique<UPIPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

// Card based payment gateway adapter class to adapt the payment gateway to the payment processor interface

class visaPaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        visaPaymentGateway() {
            paymentProcessor = make_unique<CardPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

class mastercardPaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        mastercardPaymentGateway() {
            paymentProcessor = make_unique<CardPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

class rupaycardpaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        rupaycardpaymentGateway() {
            paymentProcessor = make_unique<CardPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};

//Net banking based payment gateway adapter class to adapt the payment gateway to the payment processor interface
class hdfcbankPaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        hdfcbankPaymentGateway() {
            paymentProcessor = make_unique<NetBankingPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};


class SBIBankpaymentGateway: public IPaymentGateway
{
    private:
        unique_ptr<IPaymentProcessor> paymentProcessor;

    public:
        SBIBankpaymentGateway() {
            paymentProcessor = make_unique<NetBankingPaymentProcessor>();
        }

        unique_ptr<PaymentResponse> pay(PaymentRequest request) override {
            paymentProcessor->processPayment(request);
            return make_unique<PaymentResponse>(request.getPaymentId(), SUCEESS, "Payment successful");
        }

        unique_ptr<PaymentStatus> getPaymentStatus(string paymentId) override {
            return make_unique<PaymentStatus>(paymentId, SUCEESS);
        }

        unique_ptr<PaymentResponse> cancelPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, CANCELLED, "Payment cancelled");
        }

        unique_ptr<PaymentResponse> refundPayment(string paymentId) override {
            return make_unique<PaymentResponse>(paymentId, REFUNDED, "Payment refunded");
        }
};