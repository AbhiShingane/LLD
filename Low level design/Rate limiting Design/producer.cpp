#include <iostream>
#include <Task.h>
#include <BlockingQueue.h>

using namespace std;

class Producer
{
    BlockingQueue<Task>& queue;

    public:

    Producer(BlockingQueue<Task> & q) : queue(q){}

    void produce(int id)
    {
        Task t{id, "data"};
        queue.push(t);
    }
};