#include<iostream>
#include<gatewayfactory.h>
#include<paymentadapter.h>
#include<paymentrequest.h>
#include<paymentprocessor.h>

using namespace std;

class GatewayFactory {
    public:
        static unique_ptr<IPaymentGateway> createPaymentGateway(PaymentRequest request) {
            switch (request.getPaymentMethod()) {
                case CARD:
                    if (request.getPaymentDetails().at("cardType") == "mastercard") {
                        return make_unique<mastercardPaymentGateway>();
                    } else if (request.getPaymentDetails().at("cardType") == "rupay") {
                        return make_unique<rupaycardpaymentGateway>();
                    }
                    break;
                case NET_BANKING:
                    if (request.getPaymentDetails().at("bankName") == "hdfc") {
                        return make_unique<hdfcbankPaymentGateway>();
                    } else if (request.getPaymentDetails().at("bankName") == "sbi") {
                        return make_unique<SBIBankpaymentGateway>();
                    }
                    break;
                case UPI:
                    if (request.getPaymentDetails().at("upiProvider") == "gpay") {
                        return make_unique<gpaypaymentGateway>();
                    } else if (request.getPaymentDetails().at("upiProvider") == "phonepe") {
                        return make_unique<phonepepaymentGateway>();
                    }
                    break;
                default:
                    throw invalid_argument("Invalid payment method");
            }
        }
};