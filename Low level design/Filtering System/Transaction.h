#include<iostream>
#include<string>
#include<chrono>

using namespace std;
typedef enum
{
    COMPLETED,
    FAILED,
    CANCELLED
}TransactionStatus;

class Transaction
{
    string id;
    string name;
    double amount;
    std::time_t transactionDate;
    TransactionStatus status;
};