#include<iostream>

#include<product.h>
#include<Coupon.h>

using namespace std;

class CartItem
{
    string cartItemId;
    std::shared_ptr<Product> product;
    int quantity;
    double price;


    public:
    CartItem(string cId, std::shared_ptr<Product> p, int quantity) : cartItemId(cId), product(p), this.quantity(quantity){}

    

    double totalValueOfCartItem()
    {
        double totalVal = 0.0;
        totalVal = product->getperunitPrice() * quantity;

        price = std::move(totalVal);
        return price;
    }

    void updateQty(int qty)
    {
        if(qty <= 0)
         throw std::runtime_error("quantity should be more than 0");

         quantity = qty;
    }
};