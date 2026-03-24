#include<iostream>
#include<ConsistentHashing.h>
#include<StorageNode.h>
#include<mutex>
#include<unordered_map>

class ReplicationManager
{
    private:
    ConsistentHashing ring;
    std::unordered_map<std::string, std::shared_ptr<StorageNode>> nodes;
    int replicationFactor;

    public:
    ReplicationManager(ConsistentHashing &r, int rf) : ring(r), replicationFactor(rf){}

    ReplicationManager(const ReplicationManager& other) = delete;

    ReplicationManager& operator=(const ReplicationManager& other) = delete;

    ReplicationManager(const ReplicationManager&& other) = delete;

    ReplicationManager& operator=(const ReplicationManager& other) = delete;

    void AddNodeIntoReplicationNodelist(std::shared_ptr<StorageNode> node)
    {
        nodes[node->getID()] = node;
        ring.addNode(node);
    }

    std::vector<std::shared_ptr<StorageNode>> getReplicasOfNode(const std::string& key)
    {
        std::vector<std::shared_ptr<StorageNode>> result;

        auto nodeIds = ring.getNodes(key, replicatioFactor);
        for(auto id : nodeIds)
        {
            if(nodes.count(id))
                result.push_back(nodes[id]);
        }

        return result;
    }


}