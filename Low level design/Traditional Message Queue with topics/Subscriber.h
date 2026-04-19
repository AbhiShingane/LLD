#include<iostream>
#include<Event.h>
#include<ISubscriber>

using namespace std;

class Subscriber : public ISubscriber
{   
    private:
    string Id;
    std::function<void(const Event &)> callback;

    public:
    Subscriber(const string &id, std::function<void(const Event &)> callback): Id(id), this.callback(callback){}

    string getId() const override
    {
            return Id;
    }

    void OnEvent(const Event& event)
    {
        callback(event);
    }

};