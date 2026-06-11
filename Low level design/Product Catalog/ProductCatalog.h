#include<iostream>
#include<string>
#include "Product.h"
#include "ProductNode.h"
#include "SimilarityEdge.h"
#include<vector>
#include<unordered_map>
#include<priority_queue>
using namespace std;

class ProductCatalog
{   

    unordered_map<string, shared_ptr<ProductNode>> productGraph;

    private:
    double calculateSimilarityScore(Product *source, Product *destination)
    {
        double score = 0.0;
        if(source->getSpecificiations() == destination->getSpecificiations())
        {
            score += 1.0;
        }
        
        if(source->getPrice() == destination->getPrice())
        {
            score += 1.0;
        }

        if(source->getDescription() == destination->getDescription())
        {
            score += 1.0;
        }

        if(source->getName() == destination->getName())
        {
            score += 1.0;
        }

        return score;
    }
    public:
    ProductCatalog()
    {
        productGraph.clear();
    }

    ProductCatalog(const ProductCatalog &catalog)
    {
        this->productGraph = catalog.productGraph;
    }

    ProductCatalog& operator=(const ProductCatalog &catalog)
    {
        if(this == &catalog)
        {
            return *this;
        }
        this->productGraph = catalog.productGraph;
        return *this;
    }

    ProductCatalog(ProductCatalog &&catalog)
    {
        this->productGraph = catalog.productGraph;
        catalog.productGraph.clear();
    }

    ProductCatalog& operator=(ProductCatalog &&catalog)
    {
        if(this == &catalog)
        {
            return *this;
        }
        this->productGraph = catalog.productGraph;
        catalog.productGraph.clear();
        return *this;
    }

    void addProduct(Product *product)
    {
        productGraph[product->getId()] = make_shared<ProductNode>(product);
    }

    void addSimilarityEdge(Product *source, Product *destination, double similarityScore)
    {
        auto node1 = productGraph[source->getId()];
        auto node2 = productGraph[destination->getId()];

        double score = calculateSimilarityScore(source, destination);

        node1->neighborEdges.push_back(SimilarityEdge(node2, score));
        node2->neighborEdges.push_back(SimilarityEdge(node1, score));
        

        return;
    }

    std::vector<Product> getSimilarProducts(Product *product, double threshold)
    {
        vector<Product> similarProducts;
        auto node = productGraph[product->getId()];

        for(auto edge : node->neighborEdges)
        {
            if(edge.similarityScore >= threshold)
            {
                similarProducts.push_back(edge.destination);
            }
        }

        return similarProducts;
    }

    std::vector<Product> GetTopKSimilarProducts(Product *product, int k)
    {
        vector<Product> similarProducts;
        auto node = productGraph[product->getId()];

        priority_queue<pair<double, Product>> pq;

        for(const auto &edge : node->neighborEdges)
        {
            pq.push({edge.similarityScore, edge.destination});
            if(pq.size() > k)
            {
                pq.pop();
            }
        }

        while(!pq.empty())
        {
            similarProducts.push_back(pq.top().second);
            pq.pop();
        }

        return similarProducts;
    }

    
};