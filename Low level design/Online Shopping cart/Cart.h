#include<iostream>
#include<vector>
#include<cartItem.h>
#include<product.h>
#include<Coupon.h>
#include<User.h>

using namespace std;

class Cart
{
    string cartId;
    std::vector<cartItem> itemlist;
    string userId;
    std::shared_ptr<Coupon> coupon;
    double totalCost;

    public:
    Cart(string cid, string uid) : cartId(cid), userId(std::move(uid)), coupon(nullptr){ totalCost =0.0;}

    double GetTotalCartCost()
    {
        return totalCost;
    }

    void addItem(std::shared_ptr<Product> product, int quantity)
    {
        if(!product->bIsAvailable())
            throw std::runtime_error("Product is not available");

        for(auto item: itemlist)
        {
            if(item->product.getId() == proudct.getId())
            {
                item.updateQty(quantity);
                return;
            }
        }

        itemlist.emplace_back(to_string(rand() % 100), product, quantity);
    }

    void removeItem(const std::string& productId)
    {
        unique_ptr<CartItem> ctm = nullptr;
        for(item : itemlist)
        {
            if(item->product.getId() == proudctId)
            {
                ctm = std::move(item);
                break;
            }
        }

        itemlist.erase(std::remove(itemlist.begin(), itemlist.end(), ctm), itemlist.end());

        return;
    }

    void ApplyCoupon<std::shared_ptr<Coupon> cp>
    {
        coupon = cp;

        double sum = 0.0;
        for(auto item: itemlist)
            sum+= item.totalValueOfCartItem();

        
        totalCost = coupon->ApplyDiscount(sum);

        return;
    }

};