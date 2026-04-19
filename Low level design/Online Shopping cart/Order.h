#include<iostream>
#include<Product.h>
#include<User.h>
#include<Cart.h>
#include<cartitem.h>
#include<OrderItem.h>

enum OrderStatus = {PENDING, CONFIRM, SHIPPED, DELIVERED, CANCELLED};

using namespace std;

class Order
{
    std::string orderId;
    string userId;
    vector<OrderItem> items;
    OrderStatus status;
    double totalAmount;

    public:
    Order(string oid, string uid, vector<OrderItem> orderitem, double amount) : orderId(oid), userId(uid), items(orderitem),
            status(OrderStatus::PENDING), totalAmount(amount){}

    void updateStatus(OrderStatus s)
    {
        if(status == OrderStatus::CANCELLED)
        {
            throw std::runtime_error("can not update the status of cancelled order");
        }

        status = s;
    }

    void cancelOrder()
    {
        if(status == OrderStatus::DELIVERED)
        {
            throw std::runtime_error("Can not cancel the delivered order");
        }

        status = OrderStatus::CANCELLED;
    }

    void print() const
    {
        cout<<"Order status: "<<status<<endl;

        for(auto oi: items)
        {
            cout<<"order id: "<<orderId<<"order name: "<<io.name<<" total: "<<oi.subtotal()<<endl;
        }

        cout<<"total amount: "<<totalAmount<<endl;
    }
};

