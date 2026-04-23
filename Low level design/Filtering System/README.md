# Filtering System

A low-level design implementation of a flexible, extensible filtering system for transactions. This project demonstrates the **Filter Pattern** and design principles for building scalable filtering mechanisms with support for single and composite filters.

## Overview

The Filtering System provides a robust transaction filtering engine that allows querying transaction records based on multiple criteria such as customer name, date range, amount, and status. The system is built with extensibility in mind, enabling developers to easily add new filter types without modifying existing code.

## Architecture

### Core Components

#### 1. **Filter Interface (IFilter)**
- Base interface for all filter implementations
- Defines the contract: `bool apply(const Transaction& txn)`
- Enables polymorphic filtering behavior

#### 2. **Filter Implementations**

- **NameFilter**: Filters transactions by customer name
  - Matches exact customer names
  - Case-sensitive comparison

- **DateFilter**: Filters transactions by date range
  - Supports date range queries (start and end time)
  - Inclusive range filtering

- **AmountFilter**: Filters transactions by minimum amount
  - Filters transactions with amount >= specified threshold
  - Useful for finding high-value transactions

- **StatusFilter**: Filters transactions by status
  - Supports transaction statuses: COMPLETED, FAILED, CANCELLED
  - Exact status matching

#### 3. **CompositeFilter**
- Combines multiple filters with AND semantics
- Adds filters dynamically at runtime
- All filters must pass for a transaction to match

#### 4. **Data Model**

**Transaction**
```cpp
- id: string
- name: string (customer name)
- amount: double
- transactionDate: time_t
- status: TransactionStatus (COMPLETED, FAILED, CANCELLED)
```

#### 5. **Storage (Store)**
- Thread-safe transaction storage using `shared_mutex`
- Methods:
  - `AddTransaction()`: Add a transaction (write lock)
  - `GetAllTransaction()`: Retrieve all transactions (read lock)
- Supports concurrent read operations

#### 6. **TransactionFilterEngine**
- Core filtering engine that applies filters to transactions
- Iterates through all transactions and applies filter logic
- Returns filtered results as a vector

## Key Features

- ✅ **Multiple Filter Types**: Name, Date, Amount, Status
- ✅ **Composite Filtering**: Combine multiple filters for complex queries
- ✅ **Thread-Safe Storage**: Uses shared_mutex for safe concurrent access
- ✅ **Extensible Design**: Easy to add new filter types
- ✅ **Clean API**: Simple, intuitive public functions for common filtering operations
- ✅ **Pattern-Based**: Implements the Filter/Criteria Pattern

## Design Patterns Used

1. **Strategy Pattern**: Each filter implements a different filtering strategy
2. **Composite Pattern**: CompositeFilter combines multiple filters
3. **Template Method**: IFilter defines the filtering contract
4. **Data Access Object (DAO)**: Store manages data persistence and access

## Public API

### Single-Criteria Filters

```cpp
// Filter by customer name
std::vector<Transaction> GetRecordsByNameFilter(const std::string name, Store &store)

// Filter by minimum amount
std::vector<Transaction> GetRecordsByAmountFilter(double amount, Store &store)

// Filter by date range
std::vector<Transaction> GetRecordByDateFilter(std::time_t startdate, std::time_t endDate, Store &store)

// Filter by status
std::vector<Transaction> GetRecordByStatusFilter(TransactionStatus status)
```

### Multi-Criteria Filtering

```cpp
// Combine multiple filters (AND logic)
std::vector<Transaction> GetRecordByMultipleFilter(
    std::string name, 
    double amount, 
    TransactionStatus status, 
    Store &store
)
```

## Usage Example

```cpp
// Initialize store
Store store;

// Add transactions
store.AddTransaction({1, "C1", 500, time(nullptr), COMPLETED});
store.AddTransaction({2, "C2", 500, time(nullptr), COMPLETED});
store.AddTransaction({3, "C2", 800, time(nullptr), FAILED});

// Filter by name
auto results = GetRecordsByNameFilter("C2", store);

// Filter by amount
auto highValueTransactions = GetRecordsByAmountFilter(600, store);

// Filter by multiple criteria
auto results = GetRecordByMultipleFilter("C2", 500, COMPLETED, store);
```

## Extensibility

To add a new filter type:

1. Create a new class inheriting from `IFilter`
2. Implement the `apply()` method
3. Add a corresponding API function in TransactionFilter.h

Example:
```cpp
class CurrencyFilter : public IFilter {
    std::string currency;
public:
    CurrencyFilter(std::string cur) : currency(cur) {}
    
    bool apply(const Transaction& txn) override {
        return txn.currency == currency;
    }
};
```

## Thread Safety

- **Store**: Uses `shared_mutex` for safe concurrent access
  - Multiple readers can access simultaneously
  - Writers get exclusive access
  - Prevents race conditions

## Time Complexity

| Operation | Complexity |
|-----------|-----------|
| Add Transaction | O(1) |
| Get All Transactions | O(n) |
| Single Filter | O(n) |
| Composite Filter | O(n * m) where m = number of filters |

## Space Complexity

- Store: O(n) where n = number of transactions
- Filter results: O(k) where k = matching transactions

## Files

- `Filter.h` - Filter interface and concrete filter implementations
- `Storage.h` - Transaction storage with thread-safe access
- `Transaction.h` - Transaction data model and status enum
- `TransactionFilter.h` - Filtering engine and public API functions

## Improvements & Future Enhancements

1. **Pagination**: Support for paginated results in large datasets
2. **Performance**: Index-based filtering for faster lookups
3. **Persistence**: Database integration for permanent storage
4. **Advanced Operators**: Support for OR, NOT operators in composite filters
5. **Sorting**: Add sorting capabilities to filtered results
6. **Caching**: Cache frequently used filter results
7. **Async Filtering**: Asynchronous filtering for large datasets

## Summary

This Filtering System demonstrates a well-structured, maintainable approach to filtering with proper separation of concerns, extensibility, and thread safety. It's suitable for transaction processing systems, financial applications, or any domain requiring flexible filtering capabilities.
