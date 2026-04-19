#include<iostream>
#include<product.h>
#include<unordered_map>


using namespace std;

class productCatelog
{
    std::unordered_map<std::string, std::shared_ptr<Product>> productstore;

    public:
    void addProduct(std::shared_ptr<Product> p)
    {
        productstore[p->getId()] = p;

        return;
    }

    std::shared_ptr<Product> getProductById(std::string id)
    {
        auto it = productstore.find(id);
        if(it == productstore.end())
        {
            throw std::runtime_error("product not available in the store");
        }

        return productstore[id];
    }

    std::vector<std::shared_ptr<Product>> getProductsByCategory(std::string category)
    {
        std::vector<std::shared_ptr<Product>> plist;

        for(auto it = productstore.begin(); it != productstore.end(); ++it)
        {
            if(it->second->getCategoary() == category)
            {
                plist.push_back(it->second);
            }
        }

        return plist;
    }


    std::vector<std::shared_ptr<Product>> getProductByName(std::string name)
    {
        std::vector<std::shared_ptr<Product>> plist;
        
        for(auto it = productstore.begin(); it != productstore.end(); ++it)
        {
            if(bIsSubstrPresent(it->second->getproductname(), name))
            {
                plist.push_back(it->second);
            }
        }
        return plist;
    }
    
    private:
    bool bIsSubstrPresent(string name, string sb)
    {
        int fIndex = 0;
        int sIndex = 0;

        while(fIndex < name.size())
        {
            while(name[fIndex] == sb[sIndex])
            {
                fIndex++;
                sIndex++;
            }
            if(sIndex == sb.size()) return true;

            fIndex++;
            sIndex = 0;
        }

        return false;
    }
};