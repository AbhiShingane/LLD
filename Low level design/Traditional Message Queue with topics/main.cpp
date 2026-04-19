#include<iostream>
#include<string>
#include<Event.h>
#include<ISubscriber.h>
#include<topic.h>
#include<EventBus.h>
#include<Publisher.h>

using namespace std;


int main()
{
    EventBus eventbus;
    eventbus.CreateTopic("Order");
    eventbus.start();

    auto sub1 = std::make_shared<Subscriber>("s1", [](const Event& e)
    {cout<<"received: "<<e.payload<<endl;
    });

    auto sub2 = std::make_shared<Subscriber>("ss", [](const Event& e)
    {cout<<"received: "<<e.payload<<endl;
    });
    
    eventbus.subscribetoTopic("Order", sub1);
    eventbus.subscribetoTopic("Order", sub2);

    Publisher pubobj(bus);
    pubobj.publishEvent("Order", "Order from this");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    eventbus.shutdown();

    return 0;
}