#include<iostream>
#include<News.h>
#include<publisher.h>
#include<subscriber.h>

using namespace std;

int main()
{
    Publisher p1;
    Publisher p2;
    Publisher p3;
    Publisher p4;

    p1.PublishNews();
    p1.PublishNews();
    p1.PublishNews();
    p1.PublishNews();

    p2.PublishNews();
    p2.PublishNews();
    p2.PublishNews();
    p2.PublishNews();

    p3.PublishNews();
    p3.PublishNews();
    p3.PublishNews();

    p4.PublishNews();
    p4.PublishNews();


    Subscriber s1;
    Subscriber s2;

    s1.AddPublisher(p1);
    s1.AddPublisher(p4);

    s2.AddPublisher(p2);
    s2.AddPublisher(p3);


    vector<vector<News>> newsInfo = s1.GetXNewsForAllPublisher(2);

    vector<vector<News>> newsInfo1 = s2.GetAllNewsForAllPublisher();

    return 0;





}