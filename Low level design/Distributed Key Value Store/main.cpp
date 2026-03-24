#include<iostream>
#include<ConsistentHashing.h>
#include<coordinator.cpp>
#include<ReplicationManager.h>

using namespace std;



int main()
{
    ConsistentHashRing ring;
    ReplicationManager rm(ring, 3);


    auto n1 = std::make_shared<StorageNode>("Node1");
    auto n2 = std::make_shared<StorageNode>("Node2");
    auto n3 = std::make_shared<StorageNode>("Node3");

    rm.AddNodeIntoReplicationNodelist(n1);
    rm.AddNodeIntoReplicationNodelist(n2);
    rm.AddNodeIntoReplicationNodelist(n3);

    Coordinator coo(rm, 2, 2);

    coo.put("user1", "Bob");
    coo.put("user2", "Alice");

    auto val = coo.get("user2");

    return 0;

}