#include<iostream>
#include<EventBus.h>
#include<Event.h>

using namespace std;

class Publisher
{
    EventBus eventbus;

    public:
    Publisher(const EventBus &bus) : eventbus(bus){}

    void publishEvent(const string& topicName, const string& payload)
    {
        Event e{topicName, payload};
        eventbus.publish(e);

        return;
    }
};