#include<iostream>
#include<StorageNode.h>
#include<ConsistentHashing.h>
#include<ReplicationManager.h>

class Coordinator
{
    private:
    ReplicationManager& replicationManager;

    int ReadQuarom;
    int WriteQuraom;

    std::atomic<int> versionCounter{0};

    public:
    Coordinator(ReplicationManager &mgr, int W, int R) : replicationManager(mgr), ReadQuarom(R), WriteQuraom(W){}

    Coordinator(const Coordinator& other) = delete;

    Coordinator& operator=(const Coordinator& other) = delete;

    Coordinator(const Coordinator&& other) = delete;

    Coordinator& operator=(const Coordinator&& other) = delete;

    void put(const std::string& key, const std::string& value)
    {
        int version = ++versionCounter;

        auto replicas = replicationManager.getReplicasOfNode(key);

        int success = 0;

        for(auto replica: replicas)
        {
            replica->put(key, value, version);
            success++;
        }

        if(success < WriteQuraom)
        {
            throw std::runtime_error("write replicas failed");
        }


    }


    std::optional<std::string> get(const std::string& key)
    {
        auto replicas = replicationManager.getReplicasOfNode(key);

        int response = 0;
        int latestVersion = -1;

        std::string latestValue;

        for(auto node: replicas)
        {
            auto res = node.get(key);

            if(res)
            {
                response++;

                if(res.version > latestVersion)
                {
                    latestVersion  = res->version;
                    latestValue = res->value;
                }



            }

            if(response >= ReadQuarom)
             break;
        }

        if(latestVersion == -1) return std::nullopt;

        return latestVersion;
    }

    void removeReplicas(const std::string & key)
    {
        auto replicas = replicationManager.getReplicas(key);

        for(auto& node: replicas)
        {
            node->remove(node);
        }

        return;
    }
}