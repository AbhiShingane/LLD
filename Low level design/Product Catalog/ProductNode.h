#include<iostream>
#include<string>
#include "Product.h"
#include "SimilarityEdge.h"
#include<vector>

using namespace std;

class ProductNode
{
    public:
    Product *product;
    vector<SimilarityEdge> neighborEdges;

    ProductNode(Product *product)
    {
        this->product = product;
    }

    ProductNode()
    {
        this->product = nullptr;
    }

    ProductNode(const ProductNode &node)
    {
        this->product = node.product;
        this->neighborEdges = node.neighborEdges;
    }

    ProductNode& operator=(const ProductNode &node)
    {
        if(this == &node)
        {
            return *this;
        }
        this->product = node.product;
        this->neighborEdges = node.neighborEdges;
        return *this;
    }

    ProductNode(ProductNode &&node)
    {
        this->product = node.product;
        this->neighborEdges = node.neighborEdges;
        node.product = nullptr;
        node.neighborEdges.clear();
    }

    ProductNode& operator=(ProductNode &&node)
    {
        if(this == &node)
        {
            return *this;
        }
        this->product = node.product;
        this->neighborEdges = node.neighborEdges;
        node.product = nullptr;
        node.neighborEdges.clear();
        return *this;
    }
};