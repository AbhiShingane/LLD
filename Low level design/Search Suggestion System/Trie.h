#include<iostream>
#include<TrieNode.h>
#include<Suggestion.h>
#include<algorithm>
#include<vector>
#include<algorithm>
#include<queue>

class Trie
{
    private:
    std::unique_ptr<TrieNode> root_;

    static double computeScore(int freq, double basescore)
    {
        return basescore + static_cast<double> (freq * 1.0 + (freq > 10 ? 5.0 : 0.5) + (freq > 20 ? 20.0 : 3.5));
    }

    using Minheap = std::priority_queue<Suggestion, std::vector<Suggestion>, greater<Suggestion>>;
    public:

    Trie() : root_(std::make_unique<TrieNode>())
    {}


    void insert(const std::string &word, int frequency = 1, double score = 0.0)
    {
        if(word.size() == 0) return;

        TrieNode *ptr = root_.get();

        for(auto ch: word)
        {
            if(!ptr->children.count(ch))
            {
                ptr->children[ch] = std::make_unique<TrieNode>();
            }

            ptr = ptr->children[ch].get();
        }

        ptr->bIsEndOfWord = true;
        ptr->frequency += frequency;
        ptr->score = computeScore(ptr->frequency, score);
        ptr->fullword  = word;

        return;
    }


    void update(const std::string& word, int deltafreq = 1)
    {
        if(word.size() == 0) return;

        TrieNode *curr  = root_.get();

        for(auto ch: word)
        {
            if(!curr->children[ch])
            {
                return;
            }
            curr = curr->children[ch].get();
        }

        curr->frequency += deltafreq;
        curr->score = computeScore(curr->frequency, curr->score);

        return;
    }

    bool empty()
    {
        return root_->children.empty();
    }

    TrieNode* findNode(const std::string &word)
    {
        if(word.size() == 0) return nullptr;

        TrieNode *curr = root_.get();

        for(auto ch: word)
        {
            auto it = curr->children.find(ch);
            if(it == curr->children.end())
                return nullptr;

            curr = it->second.get();
        }

        return curr;
    }

    std::vector<Suggestion> getKSuggestion(const std::string& prefix, int topK = 5)
    {
        std::vector<Suggestion> result;

        if(prefix.size() == 0) return result;

        TrieNode *prefixEnd = findNode(prefix);

        Minheap heap;

        doDFS(prefixEnd, heap, topK);

        while(!heap.empty())
        {
            result.push_back(heap.top());
            heap.pop();
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    void doDFS(TrieNode *node, Minheap &heap, int topK)
    {
        if(!node) return;

        if(node->bIsEndOfWord)
        {
            Suggestion s{node->fullword, node->frequency, node->score};
            if(heap.size() < topK)
            {
                heap.push(s);
            }
            else if(s.score > heap.top().score)
            {
                heap.pop();
                heap.push(s);
            }
        }

        for(auto &[ch, child]: node->children)
        {
            doDFS(child.get(), heap, topK);
        }

        return;
    }
};
