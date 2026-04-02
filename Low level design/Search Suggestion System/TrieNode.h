#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<functional>


class TrieNode
{
    public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool bIsEndOfWord = false;
    int frequency = 0;
    double score = 0.0;

    std::string fullword = "";
};