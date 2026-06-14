#include<iostream>
#include<string>
#include<paymentrequest.h>
#include<paymentprocessor.h>

using namespace std;


typedef enum
{
    INITIATED,
    PROCESSING,
    COMPLETED,
    FAILED,
    CANCELLED,
    REFUNDED
}transactionStatus;

class transaction {
    private:
        string transactionId;
        string paymentId;
        double amount;
        transactionStatus status;

    public:
        transaction(string id, string pid, double amt, transactionStatus stat) {
            transactionId = id;
            paymentId = pid;
            amount = amt;
            status = stat;
        }

        string getTransactionId() {
            return transactionId;
        }

        string getPaymentId() {
            return paymentId;
        }

        double getAmount() {
            return amount;
        }

        transactionStatus getStatus() {
            return status;
        }

        transaction getTransaction() {
            return *this;
        }
};