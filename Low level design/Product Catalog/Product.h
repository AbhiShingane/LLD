#include<iostream>
#include<vector>

using namespace std;

class Product
{
    private:
        int id;
        string name;
        string description;
        double price;
        string specificiations;

    public:
        Product(int id, string name, string description, double price, string specificiations)
        {
            this->id = id;
            this->name = name;
            this->description = description;
            this->price = price;
            this->specificiations = specificiations;
        }

        Product()
        {
            this->id = 0;
            this->name = "";
            this->description = "";
            this->price = 0.0;
            this->specificiations = "";
        }

        Product(const Product &product)
        {
            this->id = product.id;
            this->name = product.name;
            this->description = product.description;
            this->price = product.price;
            this->specificiations = product.specificiations;
        }

        Product& operator=(const Product &product)
        {
            if(this == &product)
            {
                return *this;
            }
            this->id = product.id;
            this->name = product.name;
            this->description = product.description;
            this->price = product.price;
            this->specificiations = product.specificiations;
            return *this;
        }

        Product(Product &&product)
        {
            this->id = product.id;
            this->name = product.name;
            this->description = product.description;
            this->price = product.price;
            this->specificiations = product.specificiations;
            product.id = 0;
            product.name = "";
            product.description = "";
            product.price = 0.0;
            product.specificiations = "";
        }

        Product& operator=(Product &&product)
        {
            if(this == &product)
            {
                return *this;
            }
            this->id = product.id;
            this->name = product.name;
            this->description = product.description;
            this->price = product.price;
            this->specificiations = product.specificiations;
            product.id = 0;
            product.name = "";
            product.description = "";
            product.price = 0.0;
            product.specificiations = "";
            return *this;
        }

        ~Product()
        {
            this->id = 0;
            this->name = "";
            this->description = "";
            this->price = 0.0;
            this->specificiations = "";
        }

        int getId()
        {
            return id;
        }

        string getName()
        {
            return name;
        }

        string getSpecificiations()
        {
            return specificiations;
        }

        int getId()
        {
            return id;
        }

        string getName()
        {
            return name;
        }

        string getDescription()
        {
            return description;
        }

        double getPrice()
        {
            return price;
        }

        
};