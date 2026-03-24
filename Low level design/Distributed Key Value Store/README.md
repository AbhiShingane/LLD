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