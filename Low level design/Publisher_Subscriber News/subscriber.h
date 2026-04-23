#include<iostream>
#include<queue>
#include<vector>
#include<news.h>
#include<utility>
#include<thread>
#include<mutex>
#include<publisher.h>

class Subscriber
{
    std::vector<Publisher> publist;

    public:
    Subscriber(){};

    Subscriber(const Subscriber& other) = delete;
    Subscriber& operator=(const Subscriber& other) = delete;

    Subscriber(Subscriber&& other) = delete;
    Subscriber& operator=(Subscriber& other) = delete;

    ~Subscriber(){}


    void AddPublisher(const Publisher& p1)
    {
        publist.push_back(p1);
    }

    void AddPublisher(std::vector<Publisher> plist)
    {
        if(plist.size() == 0) return;

        for(int i=0; i<plist.size(); i++)
        {
            publist.push_back(plist[i]);
        }

        std::cout<<"publisher added"<<std::endl;
    }

    void RemovePublisher(const Publisher& publisher)
    {
        if(publist.size() == 0) return;

        auto it = std::find(publist.begin(), publist.end(), publisher);
        if(it != publist.end())
        {
            publist.erase(it);
        }

        return;
    }


    std::vector<News> GetAllNewsFromPublisher(int x)
    {
        std::vector<News> newslist;
        std::vector<News> news;
        for(int i=0; i<publist.size(); i++)
        {
            newslist.begin()
        }

        return
    }


    std::vector<News> GetXNewsForAllPublisher(int x)
    {
        std::vector<News> newslist;
        std::vector<News> news;
        std::priority_queue<std::pair<string, News>, std::vector<std::pair<string, News>>, std::greater<std::pair<string, News>>> pq;
        for(int i=0; i<publist.size(); i++)
        {
            newslist = publist[i].getAllNewsForPublisher();
            for(int i=0; i<newslist.size(); i++)
            {
                pq.push({newslist[i].newsId, newslist[i]});
                if(pq.size() > x)
                {
                    pq.pop();
                }
            }

        }

        while(!pq.empty())
        {
            news.push_back(pq.top().second);
            pq.pop();
        }
        
        return news;
    }

};