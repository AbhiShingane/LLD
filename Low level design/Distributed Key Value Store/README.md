1. Problem Statement:

        Design a distributed key-value store like DynamoDB/Redis (distributed mode), supporting high availability, scalability, and low latency.

2. Requirements:
    Functional:
        put(key, value);
        get(key)
        remove(key)
        Optional:
            TTL(expiry)
            Versioning

    Non-Functional:
        High availability
        highly scalable
        low latency
        Eventual consistency

3. High level architecture:

    Client → API Layer → Coordinator → Partitioning → Replication → Storage Nodes

4. High Level architecture

     Level 0 DFD:

        +---------+        +--------------------------+
        | Client  | -----> | Distributed KV Store     |
        |         | <----- | (Coordinator + Nodes)    |
        +---------+        +--------------------------+

     Level 1 DFD (Detailed components)

                                +------------------+
                                |      Client      |
                                +--------+---------+
                                        |
                                        v
                                +------------------+
                                |   Coordinator    |
                                +--------+---------+
                                        |
                        +----------------+----------------+
                        |                                 |
                        v                                 v
                +------------------+            +----------------------+
                | Consistent Hash  |            | Replication Manager  |
                |      Ring        |            +----------+-----------+
                +--------+---------+                       |
                        |                                 |
                        v                                 v
                +-----------+         +-----------+    +-----------+
                | Storage   |         | Storage   |    | Storage   |
                | Node 1    |         | Node 2    |    | Node 3    |
                +-----------+         +-----------+    +-----------+


5. Data flow key points

    1. Put Flow
        Key → hashed → mapped to nodes

        Replicated to N nodes

        Wait for quorum (W)

    2. Get Flow
        Query multiple replicas

        Collect responses

        Return latest version

    3. Important Components:

        Coordinator → routing & orchestration

        Hash Ring → partitioning

        Replication Manager → replication logic

        Storage Nodes → actual data

6. Sequence Diagram
    1. PUT operation

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


    2. Get Operation:

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


7. Performance matrices:

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


Key Formula:
    R + W > N  → Strong consistency
    R + W <= N → Eventual consistency