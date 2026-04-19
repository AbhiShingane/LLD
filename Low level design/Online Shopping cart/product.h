#include<iostream>


using namespace std;

class Product
{
    std::string product_id;
    string product_name;
    double unit_price;
    int stock;
    std::string categoary;

    public:
    Product(string pid, int pname, double unitprice, int stk, string cate) : product_id(pid)
    {}

    string getId() {return product_id;}
    string getproductname() { return product_name;}

    double getperunitPrice() { return unit_price;}

    int getAvailableStock() {return stock;}

    string getCategoary() {return categoary;}

    bool bIsAvailable()
    {
        if(stock > 0) return true;

        return false;
    }

    void reduceStock(int quanity)
    {
        int remainingStock = this->stock = quanity;
        if(remainingStock < 0)
            stock = 0;
        else
            stock = remainingStock;

            return;
    }

    

};