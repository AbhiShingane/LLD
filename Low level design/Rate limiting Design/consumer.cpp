#include <iostream>
#include <Task.h>
#include <BlockingQueue.h>
#include <Ratelimiter.h>
#include <IRateLimiter.h>

using namespace std; 

class consumer
{
    BlockingQueue<Task> &queue;
    shared_ptr<IRateLimitar> ratelimit;
    std::string consumerId;

    public:
    consumer(BlockingQueue<Task> &q, shared_ptr<IRateLimitar> rl, const string id) : queue(q), ratelimit(rl), consumerId(id){}

    void consume()
    {
        cout<<"consumer consuming item now: "<<endl;

        while(true)
        {
            Task task = queue.pop();

            if(!ratelimit->allowrequest(consumerId))
            {
                cout<<"rate limit exhausted: "<<endl;
                continue;
            }

            process(task);
        }
    }

    private:

    void process(Task task)
    {
        cout<<"processing task: "<<task.id<<"   "<<task.payload<<endl;
    }

};