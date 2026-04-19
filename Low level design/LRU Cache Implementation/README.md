Design a LRU Cache with full implementation (HashMap + Doubly Linked List). Follow-up: thread-safe version with read-write locks.


A solid LRU design has two goals:
O(1) get/put and clear eviction order. The standard way is:

HashMap → key → node (O(1) lookup)
Doubly Linked List → most-recent at head, least-recent at tail (O(1) move/remove)