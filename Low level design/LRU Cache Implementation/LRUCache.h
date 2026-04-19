#include<iostream>
#include<Node.h>
#include<string>
#include<unordered_map>

using namespace std;

class LRUCache
{
    private:
    int capacity;
    unordered_map<int, ListNode*> mp;

    ListNode *head;
    ListNode *tail;
   

    // new node added at front
    void AddNode(ListNode* node)
    {
        if(head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head = node;
            
            head->next->prev = head;
        }
    }

    void removeNode(ListNode *node)
    {
        ListNode* nextnode = node->next;
        ListNode* prevnode = node->prev;

        if(nextnode == NULL && prevnode == NULL)
        {
            head = NULL; tail= NULL;
            return;
        }

        if(nextnode == NULL)
        {
            prevnode->next = NULL;
        }
        else
        {
            prevnode->next = nextnode;
            nextnode->prev = prevnode;
        }

        return;
    }

    void moveToFront(ListNode *node)
    {
        removeNode(node);
        AddNode(node);
    }

    ListNode* removeLRUNode()
    {
        if(tail == NULL) return;

        ListNode *prevnode = tail->prev;
        if(prevnode != NULL)
        {
            prevnode->next = NULL;
        }

        ListNode *lrunode = tail;
        tail = prevnode;
    
        
        return lrunode;
    }

    public:
    LRUCache(int cap) : capacity(cap)
    {
        head = NULL;
        tail = NULL;
    }

    int get(int key)
    {
        if(!mp.count(key))
        {
            return -1;
        }

        ListNode *node = mp[key];
        moveToFront(node);
        return node->val;
    }

    int put(int key, int value)
    {
        if(mp.count(key))
        {
            ListNode *node = mp[key];
            node->val = value;
            moveToFront(node);
        }
        else
        {
            if(mp.size() == capacity)
            {
                ListNode *node = removeLRUNode();
                mp.erase(node->val);
                delete node;
            }

            ListNode *newNode = new ListNode(value);
            mp[key] = newNode;
            AddNode(newNode);
        }

        return;
    }

};