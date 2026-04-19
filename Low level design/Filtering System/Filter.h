#include<iostream>
#include<string>
#include<vector>
#include<Transaction.h>

using namespace std;

class IFilter
{
    public:
    virtual bool apply(const Transaction& txn) = 0;
    virtual ~IFilter() = 0;
};

//CustomerName filter

class NameFilter: public IFilter
{
    std::string customerName;

    public:
    NameFilter(string name): customerName(name){}
    bool apply(const Transaction& txn) override
    {
        if(customerName == txn.name)
            return true;

        return false;
    }

    ~NameFilter(){}
};

class DateFilter : public IFilter
{
    std::time_t start;
    std::time_t end;

    public:
    DateFilter(time_t st, time_t en): start(st), end(en){}

    bool apply(const Transaction &txn)
    {
        if(txn.transactionDate >= start && txn.transactionDate <= end)
        {
            return true;
        }

        return false;
    }
};


class AmountFilter: public IFilter
{
    double amount;

    public:
    AmountFilter(double amt) : amount(amt){}

    bool apply(const Transaction& txn) override
    {
        if(txn.amount >= amount)
            return true;

        return false;
    }
};

class StatusFilter: public IFilter
{
    TransactionStatus status;

    public:
    StatusFilter(TransactionStatus sts) : status(sts){}

    bool apply(const Transaction& txn) override
    {
        if(txn.status == status) return true;

        return false;
    }
};

class CompositeFilter: public IFilter
{
    std::vector<std::shared_ptr<IFilter>> filters;

    public:
    void addFilter(std::shared_ptr<IFilter> filter)
    {
        filters.push_back(filter);
    }

    bool apply(const Transaction& txn)
    {
        for(auto f: filters)
        {
            if(!f->apply(txn))
            {
                return false;
            }
        }
        
        return true;
    }

};