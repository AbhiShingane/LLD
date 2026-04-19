#include<iostream>
#include<vector>
#include<Cart.h>


using namespace std;

class User
{
    std::string userId;
    std::string name;
    string email;

    std::shared_ptr<Cart> cart;

    public:
    User(string uid, string name, string email, std::shared_ptr<Cart> c): userId(uid), name(name), email(email),
    {
        cart = std::shared_ptr<Cart>("cart:" + userId, userId);
    }

    std::shared_ptr<Cart> getCart() {return cart;}



};