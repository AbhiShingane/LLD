# Distributed Key-Value Store

A low-level design implementation of a **distributed, highly-available key-value store** similar to DynamoDB or Redis in distributed mode. This project demonstrates core concepts in distributed systems including consistent hashing, replication, quorum-based consensus, and versioning.

## Table of Contents

- [Problem Statement](#problem-statement)
- [Requirements](#requirements)
- [System Architecture](#system-architecture)
- [Core Components](#core-components)
- [Key Concepts](#key-concepts)
- [Project Structure](#project-structure)
- [Building and Running](#building-and-running)
- [Usage Examples](#usage-examples)
- [Design Patterns & Trade-offs](#design-patterns--trade-offs)

---

## Problem Statement

Design a distributed key-value store that:
- Handles large-scale data across multiple nodes
- Maintains high availability even when nodes fail
- Provides low-latency access to data
- Ensures eventual consistency across replicas
- Supports automatic load balancing and node scaling

### Real-World Applications
- DynamoDB (AWS)
- Cassandra
- Redis Cluster
- HBase

---

## Requirements

### Functional Requirements

| Requirement | Description |
|------------|-------------|
| `put(key, value)` | Store a key-value pair |
| `get(key)` | Retrieve a value by key |
| `delete(key)` | Remove a key-value pair |
| **Optional** |
| TTL/Expiry | Auto-delete keys after expiration |
| Versioning | Track data versions for conflict resolution |

### Non-Functional Requirements

| Requirement | Target |
|------------|--------|
| **Availability** | High availability; tolerate node failures |
| **Scalability** | Horizontal scaling with multiple nodes |
| **Latency** | Low-latency read/write operations |
| **Consistency** | Eventual consistency (AP over CP) |
| **Throughput** | Support high concurrent requests |

---

## System Architecture

### High-Level Architecture

```
┌────────────┐
│   Client   │
└─────┬──────┘
      │ put/get/delete
      ▼
┌─────────────────────────────────────────────────┐
│            Coordinator (API Layer)              │
│  - Routes requests to correct nodes             │
│  - Handles quorum-based consensus               │
│  - Maintains version counters                   │
└──────────────┬────────────────────────────────┘
               │
      ┌────────┴────────┐
      │                 │
      ▼                 ▼
┌──────────────────┐  ┌─────────────────────────┐
│ Consistent Hash  │  │ Replication Manager     │
│ Ring (CH)        │  │ - Manages replicas      │
│ - Node mapping   │  │ - Replica distribution  │
│ - Virtual nodes  │  │ - Node health tracking  │
└────────┬─────────┘  └──────────┬──────────────┘
         │                       │
         └───────────┬───────────┘
                     ▼
    ┌───────────────────────────────────┐
    │  Storage Nodes (Replicated)       │
    │  ┌─────────────┬────────────────┐ │
    │  │   Node 1    │    Node 2      │ │
    │  │ {K: (V, V)} │ {K: (V, V)}    │ │
    │  └─────────────┴────────────────┘ │
    │  ┌─────────────┐                  │
    │  │   Node 3    │                  │
    │  │ {K: (V, V)} │                  │
    │  └─────────────┘                  │
    └───────────────────────────────────┘
```

### Data Flow

**Write Operation (put):**
```
Client → Coordinator → [Version++] → Replication Manager 
    → Consistent Hash Ring → Select N replicas → Write to replicas 
    → Check Write Quorum → Return Success/Failure
```

**Read Operation (get):**
```
Client → Coordinator → Replication Manager → Consistent Hash Ring 
    → Select N replicas → Read from replicas → Compare versions 
    → Return latest value if Read Quorum met
```

---

## Core Components

### 1. **ConsistentHashing.h**

Implements consistent hashing for uniform data distribution across nodes.

**Key Features:**
- Virtual nodes for better load balancing
- Thread-safe operations using `std::shared_mutex`
- O(log N) node lookup complexity

**Key Methods:**
```cpp
void addNode(const std::string &node);           // Add node to ring
void removeNode(const std::string &node);        // Remove node from ring
std::vector<std::string> getNodes(const std::string key, int count);
                                                 // Get N nodes for a key
```

**How It Works:**
- Each physical node has multiple virtual nodes
- Reduces impact of node failures
- Provides better data distribution

### 2. **StorageNode.h**

Represents a single node in the distributed system storing key-value pairs.

**Key Features:**
- Version tracking for conflict resolution
- Thread-safe storage using `std::mutex`
- In-memory data structure (unordered_map)

**Data Structure:**
```cpp
struct Entry {
    std::string value;
    int version;
};
```

**Key Methods:**
```cpp
void put(const std::string& key, const std::string &value, int version);
std::optional<Entry> get(const std::string& key);
void remove(const std::string &key);
std::string getID();
```

**Versioning:** Higher version values always overwrite lower versions, enabling eventual consistency.

### 3. **ReplicationManager.h**

Manages data replication across multiple nodes.

**Key Responsibilities:**
- Maintain node registry
- Determine replica placement using consistent hashing
- Handle node join/leave operations

**Key Methods:**
```cpp
void AddNodeIntoReplicationNodelist(std::shared_ptr<StorageNode> node);
std::vector<std::shared_ptr<StorageNode>> getReplicasOfNode(const std::string& key);
```

**Replication Factor:** Number of copies of each data item (typically 3)

### 4. **Coordinator.h**

Orchestrates read/write operations and enforces quorum consensus.

**Key Responsibilities:**
- Route client requests to appropriate nodes
- Implement read/write quorum logic
- Maintain global version counter

**Key Methods:**
```cpp
void put(const std::string& key, const std::string& value);
std::optional<std::string> get(const std::string& key);
void removeReplicas(const std::string & key);
```

**Quorum-Based Consistency:**
- **Write Quorum (W):** Minimum replicas that must acknowledge write
- **Read Quorum (R):** Minimum replicas that must respond to read
- If W + R > Replication Factor → Strong consistency
- If W + R ≤ Replication Factor → Eventual consistency

---

## Key Concepts

### 1. Consistent Hashing

**Problem It Solves:** Minimize data redistribution when nodes are added/removed.

**Solution:**
- Map both keys and nodes to a hash ring
- A key is stored on the N nodes clockwise from its hash position
- Virtual nodes reduce load imbalance

**Benefits:**
- O(K/N) data movement on node failure (K = total keys, N = num nodes)
- vs. O(K) with traditional hashing

**Example:**
```
Ring: [Node1, VN1, Node2, VN2, Node3, VN3]
Key "user:123" → Hash value points to Node2 + 2 replicas
```

### 2. Replication

**Replication Factor (RF):** Number of copies of each key

**Strategy:**
- Write to first RF nodes in consistent hash ring
- Provides fault tolerance and read scaling
- RF = 3 means tolerating 2 node failures

### 3. Quorum-Based Consensus

**Write Quorum (W):** How many replicas must acknowledge write before success
**Read Quorum (R):** How many replicas must respond before returning value

**Consistency Levels:**
- **Strong Consistency:** W + R > RF (e.g., W=3, R=2, RF=3)
- **Eventual Consistency:** W + R ≤ RF (e.g., W=1, R=1, RF=3)
- **Typical (DynamoDB):** W=1, R=1, RF=3 for low latency

### 4. Versioning

**Version Counter:**
- Incremented on every write
- Attached to each value
- Used during reads to return latest value

**Conflict Resolution:**
- Higher version always wins
- Ensures eventual consistency across replicas
- Background process syncs missing replicas

### 5. Thread Safety

All components use synchronization primitives:
- `std::mutex` for exclusive access
- `std::shared_mutex` for concurrent reads

---

## Project Structure

```
Distributed Key Value Store/
├── ConsistentHashing.h       # Consistent hashing ring implementation
├── StorageNode.h             # Individual storage node
├── ReplicationManager.h       # Manages replication across nodes
├── Coordinator.h             # Orchestrates read/write operations
├── coordinator.cpp           # Coordinator implementation
├── main.cpp                  # Demo/test driver
└── README.md                 # This file
```

---

## Building and Running

### Prerequisites
- C++17 or later
- Standard library support for `std::optional`, `std::shared_ptr`, `std::mutex`
- CMake (optional) or your preferred build system

### Compilation (g++ example)

```bash
# Simple compilation
g++ -std=c++17 -o kvstore main.cpp

# With debugging symbols
g++ -std=c++17 -g -o kvstore main.cpp

# With optimization
g++ -std=c++17 -O2 -o kvstore main.cpp
```

### Running

```bash
./kvstore
```

---

## Usage Examples

### Basic Usage

```cpp
#include "ConsistentHashing.h"
#include "StorageNode.h"
#include "ReplicationManager.h"
#include "Coordinator.h"

int main() {
    // 1. Create consistent hash ring
    ConsistentHashing ring(3); // 3 virtual nodes per physical node
    
    // 2. Create replication manager with RF=3
    ReplicationManager rm(ring, 3);
    
    // 3. Create storage nodes
    auto node1 = std::make_shared<StorageNode>("Node1");
    auto node2 = std::make_shared<StorageNode>("Node2");
    auto node3 = std::make_shared<StorageNode>("Node3");
    
    // 4. Register nodes
    rm.AddNodeIntoReplicationNodelist(node1);
    rm.AddNodeIntoReplicationNodelist(node2);
    rm.AddNodeIntoReplicationNodelist(node3);
    
    // 5. Create coordinator with W=2, R=2
    Coordinator coordinator(rm, 2, 2);
    
    // 6. Perform operations
    coordinator.put("user:1", "Alice");
    coordinator.put("user:2", "Bob");
    
    auto value = coordinator.get("user:1");
    if (value) {
        std::cout << "Value: " << value.value() << std::endl;
    }
    
    return 0;
}
```

### Adding/Removing Nodes (Scaling)

```cpp
// Adding a new node
auto node4 = std::make_shared<StorageNode>("Node4");
rm.AddNodeIntoReplicationNodelist(node4);  // Data automatically redistributed

// Removing a node (handled by ring)
rm.removeNode("Node4");  // Replicas on other nodes ensure availability
```

---

## Design Patterns & Trade-offs

### 1. **Quorum Consistency Trade-off**

| Setting | Consistency | Availability | Latency |
|---------|-------------|--------------|---------|
| W=1, R=1 | Eventual | High | Low |
| W=RF, R=1 | Strong | Medium | Medium |
| W=1, R=RF | Eventually Consistent | High | Medium |
| W=RF/2, R=RF/2 | Tunable | High | Medium |

### 2. **Virtual Nodes**

**Why?**
- Without virtual nodes: Node failure = large data transfer to one node
- With virtual nodes: Data evenly distributed among remaining nodes

**Trade-off:** More virtual nodes = better distribution but higher memory overhead

### 3. **Version Vectors vs. Simple Versioning**

**Current Implementation:** Simple integer versioning
- Pros: Lightweight, easy to implement
- Cons: Can't detect concurrent writes, only total ordering

**Alternative:** Vector clocks
- Pros: Detect causality
- Cons: Higher overhead, complex reconciliation

### 4. **Read-Write Splits**

**Benefits:**
- Separate read and write quorums for flexibility
- Read-heavy workloads: low R, high W
- Write-heavy workloads: low W, high R

### 5. **Thread Safety Strategy**

- Consistent Hash Ring: `std::shared_mutex` (many readers, few writers)
- Storage Node: `std::mutex` (balanced access patterns)
- Coordinator: `std::atomic<int>` for version counter

---

## Performance Characteristics

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| put() | O(log N + RF) | Hash lookup + write to RF nodes |
| get() | O(log N + RF) | Hash lookup + read from RF nodes |
| Node addition | O(K/N) | Redistribute ~K/N keys |
| addNode() | O(1) amortized | Virtual nodes add constant overhead |

---

## Limitations & Future Enhancements

### Current Limitations
1. **In-Memory Only:** Data lost on shutdown (no persistence)
2. **Simple Versioning:** No causality tracking (consider vector clocks)
3. **No TTL:** Keys never expire automatically
4. **No Read Repair:** Stale replicas not automatically updated
5. **Synchronous Replication:** Writes block until quorum confirmed

### Potential Enhancements
- [ ] Disk persistence (LSM trees, WAL)
- [ ] TTL/expiration mechanism
- [ ] Read repair and anti-entropy background processes
- [ ] Async replication for better latency
- [ ] Conflict-free replicated data types (CRDTs)
- [ ] Monitoring & observability
- [ ] Client connection pooling
- [ ] Partition tolerance handling (split-brain scenarios)

---

## Testing Considerations

To validate the implementation, test:
1. **Basic Operations:** put/get/delete work correctly
2. **Consistency:** Multiple clients see same version
3. **Replication:** Data replicated across nodes
4. **Quorum:** Writes succeed only after quorum met
5. **Node Failure:** System continues with RF-1 nodes down
6. **Scaling:** New nodes receive fair share of keys

---

## Sequence Diagrams

### PUT Operation

```
Client        Coordinator     HashRing     ReplicationMgr     Node1     Node2     Node3
  |                |              |              |              |         |         |
  |--- PUT(k,v) -->|              |              |              |         |         |
  |                |--- hash(k) ->|              |              |         |         |
  |                |<-- nodes ----|              |              |         |         |
  |                |---- replicas -------------> |              |         |         |
  |                |                             |--- PUT ----->|         |         |
  |                |                             |--- PUT ------------->  |         |
  |                |                             |--- PUT ------------------------->|
  |                |                             |<-- ACK ------|         |         |
  |                |                             |<-- ACK ------------|  |         |
  |                |                             |<-- ACK ----------------------|   |
  |                |<--- quorum satisfied -------|              |         |         |
  |<-- SUCCESS ----|              |              |              |         |         |
```

### GET Operation

```
Client        Coordinator     HashRing     ReplicationMgr     Node1     Node2     Node3
  |                |              |              |              |         |         |
  |--- GET(k) ---->|              |              |              |         |         |
  |                |--- hash(k) ->|              |              |         |         |
  |                |<-- nodes ----|              |              |         |         |
  |                |---- replicas -------------> |              |         |         |
  |                |                             |--- GET ----->|         |         |
  |                |                             |--- GET ------------->  |         |
  |                |                             |--- GET ------------------------->|
  |                |                             |<-- value ---|         |         |
  |                |                             |<-- value -----------| |         |
  |                |                             |<-- value ---------------------| |
  |                |<--- responses --------------|              |         |         |
  |                |--- resolve latest version --|              |         |         |
  |<-- VALUE ------|              |              |              |         |         |
```

---

## Performance Metrics

| Metric            | Description         | Expected                        |
| ----------------- | ------------------- | ------------------------------- |
| Read Latency      | Time to fetch value | O(R network calls)              |
| Write Latency     | Time to persist     | O(W network calls)              |
| Throughput        | Requests/sec        | High (horizontal scaling)       |
| Availability      | System uptime       | High (replication)              |
| Consistency       | Data correctness    | Tunable (R + W vs N)            |
| Scalability       | Add nodes           | Linear scaling                  |
| Fault Tolerance   | Node failures       | Tolerates N - W failures        |
| Load Distribution | Across nodes        | Balanced via consistent hashing |

**Key Formula:**
- **R + W > N** → Strong consistency
- **R + W ≤ N** → Eventual consistency

---

## References & Further Reading

- **Consistent Hashing:** Karger et al., "Consistent Hashing and Random Trees"
- **Dynamo Paper:** "Dynamo: Amazon's Highly Available Key-value Store"
- **Quorum Consistency:** "Designing Data-Intensive Applications" by Martin Kleppmann
- **Distributed Systems:** "Distributed Systems" by Maarten van Steen

---

## License

This is an educational low-level design implementation created for learning purposes.

---

## Author Notes

This implementation focuses on core distributed systems concepts:
- How data is distributed across multiple nodes
- Trade-offs between consistency, availability, and partition tolerance (CAP theorem)
- How systems achieve fault tolerance through replication
- Quorum-based consensus for distributed agreement

It simplifies many aspects of production systems (persistence, failover detection, repair mechanisms) to focus on the fundamental architectural patterns.