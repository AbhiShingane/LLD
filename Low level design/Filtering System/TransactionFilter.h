#include<iostream>
#include<Filter.h>
#include<Transaction.h>
#include<Storage.h>
#include<string>
#include<vector>

using namespace std;

class TransactionFilterEngine
{
    Store& store;

    public:

    TransactionFilterEngine(Store &s): store(s){}

    vector<Transaction> filter(std::shared_ptr<IFilter> filter)
    {
        std::vector<Transaction> result;

        auto data = store.GetAllTransaction();

        for(auto txn: data)
        {
            if(filter->apply(txn))
            {
                result.push_back(txn);
            }
        }

        return result;
    }
};


// Public APIS

Store store;

store.AddTransaction({1, "C1", 500, time(nullptr)}, COMPLETED);
store.AddTransaction({2, "C2", 500, time(nullptr)}, COMPLETED);
store.AddTransaction({3, "C2", 800, time(nullptr)}, FAILED);





std::vector<Transaction> GetRecordsByNameFilter(const std::string name,Store &store)
{
    TransactionFilterEngine filterengine(store);
    auto namefilter = std::make_shared<NameFilter>(name);
    vector<Transaction> nameFilteredData = filterengine.filter(namefilter);

    return nameFilteredData;
}

std::vector<Transaction> GetRecordsByAmountFilter(double amount, Store &store)
{
     TransactionFilterEngine filterengine(store);
    auto namefilter = std::make_shared<AmountFilter>(amount);
    vector<Transaction> AmountFilteredData = filterengine.filter(namefilter);

    return AmountFilteredData;
}

std::vector<Transaction> GetRecordByDateFilter(std::time_t startdate, std::time_t endDate, Store &store)
{
    TransactionFilterEngine filterengine(store);
    auto DateFilter = std::make_shared<DateFilter>(startdate, endDate);
    vector<Transaction> dateFilterData = filterengine.filter(DateFilter);

    return dateFilterData;
}

std::vector<Transaction> GetRecordByStatusFilter(TransactionStatus status)
{
    TransactionFilterEngine filterengine(store);
    auto statusfilter = std::make_shared<StatusFilter>(status);
    vector<Transaction> statusFilterData = filterengine.filter(statusfilter);

    return statusFilterData;
}

std::vector<Transaction> GetRecordByMultipleFilter(std::string name, double amount, Status status, Store &store)
{
    TransactionFilterEngine filterengine(store);
    auto compositefilter = std::make_shared<CompositeFilter>();
    compositefilter->addfilter(std::make_shared<NameFilter>(name));
    compositefilter->addfilter(std::make_shared<AmountFilter>(amount));
    compositefilter->addfilter(std::make_shared<StatusFilter>(status));

    vector<Transaction> compositefilterdata = filterengine.filter(compositefilter);

    return compositefilterdata;
}