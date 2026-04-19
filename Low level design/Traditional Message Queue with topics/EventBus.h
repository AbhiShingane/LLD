#include<iostream>
#include<Event.h>
#include<Subscriber.h>
#include<string>
#include<vector>
#include<unordered_map>
#include<mutex>
#include<topic.h>
#include<queue>

using namespace std;


class EventBus
{
    unordered_map<std::string, shared_ptr<Topic>> topics;
    queue<Event> eventqueue;

    condition_variable cv;
    mutex mtx;
    bool bIsstop = false;

    public:
    EventBus(){}

    void CreateTopic(string topicname)
    {
        std::lock_guard<mutex> lock(mtx);
        topics[topicname] = make_shared<Topic>(topicname);
    }

    void subscribetoTopic(const std::string &topicName, std::shared_ptr<ISubscriber> sub)
    {
        std::lock_guard<mutex> lock(mtx);
        topics[topicName]->subscribe(sub);
    }

    void unsubscribe(const std::string topicname, std::shared_ptr<ISubscriber> sub)
    {
        std::lock_guard<mutex> lock(mtx);
        topics[topicname]->unsubsribe(sub);

    }

    void publish(const Event& event)
    {
        {
            std::lock_guard<mutex> lock(mtx);
            eventqueue.push(event);
        }
        cv.notify_one();
    }

    void start()
    {
        std::thread([this](){
            while(1)
            {
                Event event;
                {
                    std::unique_lock<std::mutex> lock(mtx);

                    cv.wait(lock, [&] () {return !eventqueue.empty() && bIsstop;});
                    
                    if(eventqueue.empty() || bIsstop) break;

                    event = eventqueue.front();
                    eventqueue.pop();

                    //cv.notify_one();
                }
                dispatch(event);
            }
        }).detach();
    }

    void dispatch(const Event& event)
    {
        auto topic = event.topic;
        vector<std::shared_ptr<ISubscriber>> sublist;

        sublist = topics[topic]->getAllSubscriber();

        for(auto s: sublist)
        {
            s->OnEvent(event);
        }

        return;
    }

    void shutdown()
    {
        bIsstop = true;
        cv.notify_all();
    }

};