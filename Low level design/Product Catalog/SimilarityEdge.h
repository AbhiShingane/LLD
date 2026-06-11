#include<iostream>
#include<string>
#include"Product.h"

using namespace std;

class SimilarityEdge
{
    public:
    Product *destination;
    double similarityScore;

    SimilarityEdge(Product *destination, double similarityScore)
    {
        this->destination = destination;
        this->similarityScore = similarityScore;
    }
       
    SimilarityEdge()
    {
        this->destination = nullptr;
        this->similarityScore = 0.0;
    }

    SimilarityEdge(const SimilarityEdge &edge)
    {
        this->destination = edge.destination;
        this->similarityScore = edge.similarityScore;
    }

    SimilarityEdge& operator=(const SimilarityEdge &edge)
    {
        if(this == &edge)
        {
            return *this;
        }
        this->destination = edge.destination;
        this->similarityScore = edge.similarityScore;
        return *this;
    }

    SimilarityEdge(SimilarityEdge &&edge)
    {
        this->destination = edge.destination;
        this->similarityScore = edge.similarityScore;
        edge.destination = nullptr;
        edge.similarityScore = 0.0;
    }

    SimilarityEdge& operator=(SimilarityEdge &&edge)
    {
        if(this == &edge)
        {
            return *this;
        }
        this->destination = edge.destination;
        this->similarityScore = edge.similarityScore;
        edge.destination = nullptr;
        edge.similarityScore = 0.0;
        return *this;
    }

    ~SimilarityEdge()
    {
        this->destination = nullptr;
        this->similarityScore = 0.0;
    }
   
};