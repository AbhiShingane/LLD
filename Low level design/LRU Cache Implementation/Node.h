#include<iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;

    ListNode(int v): val(v), next(NULL), prev(NULL);
};


get - o(1);

put-> o(1);