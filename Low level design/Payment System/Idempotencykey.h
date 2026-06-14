#include<iostream>
#include<paymentadapter.h>
#include<paymentrequest.h>
#include<paymentprocessor.h>
#include<transaction.h>

using namespace std;

// The IdempotencyKey class is used to generate and manage idempotency keys for payment requests. It ensures that duplicate payment requests with the same idempotency key are not processed multiple times, preventing issues such as double charging. The class provides a method to generate a unique idempotency key for each payment request, which can be stored and checked against incoming requests to maintain idempotency in the payment processing system.
class IdempotencyKey {
    private:
        unordered_map<string, bool> keyStore;

    public:
        bool isDuplicate(string key) {
            // Check if the idempotency key already exists in the store
            return keyStore.find(key) != keyStore.end();
        }

        bool storeKey(string key) {
            // Store the idempotency key in the store
            if (isDuplicate(key)) {
                return false; // Key already exists, duplicate request
            }
            keyStore[key] = true; // Store the new key
            return true; // Key stored successfully
        }

        bool getkeyStatus(string key) {
            // Get the status of the idempotency key
            return isDuplicate(key);
        }

        

};  