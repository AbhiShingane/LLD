#include<iostream>
#include<Product.h>
#include<User.h>

using namespace std;

struct OrderItem
{
    string producId;
    string name;
    int quantity;
    double priceAtOrder;

    double subtotal()
    {
        return priceAtOrder * quantity;
    }
};