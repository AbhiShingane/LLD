#include<iostream>
#include<Event.h>
#include<Subscriber.h>
#include<string>
#include<vector>
#include<unordered_map>
#include<mutex>

using namespace std;

class Topic
{
    mutex mtx;
    string name;
    unordered_map<std::string, shared_ptr<ISubscriber>> subscribers;


    public:
    Topic(const std::string name) : this->name(name) {}

    void subscribe(std::shared_ptr<ISubscriber> sub)
    {
        std::lock_guard<mutex> lock(this->mtx);
        subscribers[sub->getId()] = sub;
    }

    void unsubsribe(std::shared_ptr<ISubscriber> sub)
    {
        std::lock_guard<mutex> lock(this->mtx);
        subscribers.erase(sub->getId());
    }

    std::vector<std::shared_ptr<ISubscriber>> getAllSubscriber() {

        std::lock_guard<std::mutex> lock(this->mtx);
        std::vector<std::shared_ptr<ISubscriber>> sublist;
        for(auto& [id, sub] : subscribers)
        {
            sublist.push_back(sub);
        }

        return sublist;
    }
};