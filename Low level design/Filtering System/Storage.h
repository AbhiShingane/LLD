#include<iostream>
#include<vector>
#include<Transaction.h>
#include<shared_mutex>

class Store
{
    std::vector<Transaction> transactionlist;
    mutable std::shared_mutex rwlock;

    public:
    Store(){}


    void AddTransaction(Transaction &t)
    {
        std::unique_lock<std::shared_mutex> lock(rwlock);
        transactionlist.push_back(t); 
    }

    std::vector<Transaction> GetAllTransaction()
    {
        std::unique_lock<std::shared_mutex> lock(rwlock);

        if(transactionlist.size() == 0) return {};

        return transactionlist;
    }
};