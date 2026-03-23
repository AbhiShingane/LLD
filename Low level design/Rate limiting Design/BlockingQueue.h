#include<iostream>
#include<Task.h>
#include<queue>
#include<mutex>
#include<condition_variable>

template <typename T>
class BlockingQueue
{
    std::queue<T> que;
    std::Mutex mtx;
    std::condition_variable cv;

    public:
    BlockingQueue(){}
    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue& operator=(const BlockingQueue& other) = delete;

    public:
    void push(T item)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [] {return !que.empty();});
        que.push(item);

        cout<<item<<" is added to the queue"<<endl;
        cv.notify_one();
    }


    T pop()
    {
        std::unique_lock<std::mutex> lock(mtx);

        T data = que.front();
        q.pop();

        return T;
    }
}