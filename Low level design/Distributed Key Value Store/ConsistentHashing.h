#include<iostream>
#include<map>
#include<algorithm>
#include<string>
#include<functional>


class ConsistentHashing
{
    private:

    std::map<size_t, std::string> ring;
    int virtualNodes;

    mutable std::shared_mutex mtx;

    size_t gethash(const std::string& key)
    {
        return std::hash<std::string>{}(key);
    }


    public:
    ConsistentHashing(int num) : virtualNodes(num){}

    ConsistentHashing(const ConsistentHashing&) = delete;
    ConsistentHashing& operator=(const ConsistentHashing&) = delete;

    ConsistentHashing(const ConsistentHashing&&) = delete;
    ConsistentHashing& operator=(const ConsistentHashing&&) = delete; 

    void addNode(const std::string &node)
    {
        std::unique_lock<std::shared_mutex> lock(mtx);

        for(int i=0; i<virtualNodes; i++)
        {
            std::string virtualNode = node + "#" + std::to_string(i);
            size_t h = gethash(virtualNode);
            ring[h] = node;
        }
    }

    void removeNode(const std::string &node)
    {
        std::unique_lock<std::shared_mutex> lock(mtx);

        for(int i=0; i<virtualNodes; i++)
        {
            std::string vnode = node + "#" + std::to_string(i);

            size_t h = gethash(vnode);

            ring.erase(h);
        }
    }

    std::vector<std::string> getNodes(const std::string key, int count)
    {
        std::unique_lock<std::shared_mutex> lock(mtx);
        
        std::vector<std::string> result;

        if(ring.empty()
        {
            throw std::runtime_error("No nodes available");
        }

        size_t h = gethash(key);

       auto it = ring.lower_bound(h);

        

        while(result.size() < count)
        {
            if(it == ring.end())
                it = ring.begin();

            if(std::find(result.begin(), result.end(), it->second) == it->second)
            {
                result.push_back(it->second;)
            }

            ++it;
        }
            
        return result;
    )
    

};
