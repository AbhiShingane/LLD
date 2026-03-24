#include<iostream>
#include<vector>
#include<queue>
#include<deque>
#include<functional>
#include<random>
#include<mutex>
#include<condition_variable>

class WorkStealThreadPool
{
    int numOfThreads;
    struct worker
    {
        std::deque<std::function<void()>> dq;
        std::mutex mtx;
    };

    std::vector<worker> workerqueue;
    std::vector<std::thread> threads;
    bool bIsStop;
    
    public:
    WorkStealThreadPool(int n) : numOfThreads(n)
    {
        for(int i=0; i<numOfThreads; i++)
        {
            workerqueue.push_back(std::make_unique<worker>());
        }

        for(int i=0; i<numOfThreads; i++)
        {
            threads.emplace_back([this, i](){
                workerloop(i);
            });
        }
    }

    WorkStealThreadPool(const WorkStealThreadPool&) = delete;
    WorkStealThreadPool& operator=(const WorkStealThreadPool&) = delete;
    WorkStealThreadPool(WorkStealThreadPool&&) = delete;
    WorkStealThreadPool& operator=(WorkStealThreadPool&&) = delete;
    
    ~WorkStealThreadPool()
    {
        bIsStop = true;

        for(auto& t: threads)
        {
            t.join();
        }
    }

    void Submit(std::function<void()> task)
    {
        int idx = rand() % numOfThreads;

        auto &work = workerqueue[idx];

        std::lock_guard<std::mutex> lock(work.mtx);
        work.dq.push_back(task);

        return;
    }

    private:

    void workerloop(int id)
    {
        if(!bIsStop)
        {
            std::function<void()> task;

            if(popOwnTask(id, task))
            {
                task();
                continue;
            }

            if(StealtaskfromOther(id, task))
            {
                task();
                continue;
            }

            std::this_thread::yield();
        }
    }

    bool popOwnTask(int id, std::function<void()> task)
    {
        auto& work = workerqueue[id];

        std::unique_lock<std::mutex> lock(mtx);
        if(!work.dq.empty())
        { 
            task = std::move(work.dq.back());
            work.dq.pop_back();
            return true;
        }

        return false;
    }

    bool StealtaskfromOther(int id, std::function<void()> task)
    {
        for(int i=0; i<numOfThreads; i++)
        {
            if(id == i) continue;

            auto& victim = workerqueue[i];
            std::lock_guard<std::mutex> lock(victim.mtx);
            if(!victim.dq.empty())
            {
                task = std::move(victim.dq.pop_front());
                victim.dq.pop_front();
                return true;
            }
        }

        return false;
    }


};
