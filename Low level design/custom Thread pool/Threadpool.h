#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<functional>
#include<vector>

class CustomThreadPool
{
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex mtx;

        std::condition_variable cv;
        bool bIsStop;
    public:
        CustomThreadPool(int numThreads)
        {
            for(int i=0; i<numThreads; i++)
            {
                workers.emplace_back([this](){
                    std::function<void()> task;
                    {
                        

                        std::unique_lock<std::mutex> lock(mtx);
                        this->cv.wait(lock, [this] { !this->tasks.empty() && !this->bIsStop; });

                        if(this->tasks.empty() || this->bIsStop)
                            return;

                        task = this->tasks.front();
                        this->tasks.pop();
                    }
                    
                    task();

                });
            }
        }

        CustomThreadPool(const CustomThreadPool&) = delete;
        CustomThreadPool& operator=(const CustomThreadPool&) = delete;
        CustomThreadPool(CustomThreadPool&&) = delete;
        CustomThreadPool& operator=(CustomThreadPool&&) = delete;
        
        void OnSubMitTask(std::function<void()> tasks)
        {
            std::lock_guard<std::mutex> lock(mtx);

            if(bIsStop)
            {
                throw std::runtime_error("thread pool is stopped.");
            }

            this->tasks.push(std::move(tasks));
            
            cv.notify_one();
            std::cout<<"task submitted"<<std::endl;    
            return;
        }

        ~CustomThreadPool()
        {
            std::unique_lock<std::mutex> lock(mtx);

            bIsStop = true;

            cv.notify_all();

            for(int i=0; i<workers.size(); i++)
            {
                workers[i].join();
            }
        }
};