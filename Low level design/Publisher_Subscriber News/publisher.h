#include<iostream>
#include<queue>
#include<vector>
#include<news.h>
#include<utility>
#include<thread>
#include<mutex>



class Publisher
{
    //std::priority_queue<std::pair<int, News>> pq;
    std::vector<std::pair<int, News>> newsStore;
    int newsCounter; 

    public:
    Publisher():newsCounter(1){};

    Publisher(const Publisher& other) = delete;
    Publisher& operator=(const Publisher& other) = delete;

    Publisher(Publisher&& other) = delete;
    Publisher& operator=(Publisher&& other) = delete;

    ~Publisher(){}

    void PublishNews()
    {
        //publishing the news
        News n1("abc", "abc", "abc", 2);
        
        //adding into the storage
        //pq.push({newsCounter++, n1});
        newsStore.insert(newsStore.begin(), {newsCounter++, n1});
    }


    std::vector<News> getAllNewsForPublisher()
    {
        std::vector<News> newslist;
        for(auto it = newsStore.begin(); it != newsStore.end(); ++it)
        {
             newslist.push_back(it->second);
        }

        return newslist;
        
    }

    std::vector<News> getXNewsForPublisher(int x)
    {
        std::vector<News> newslist;

        for(auto it = newsStore.begin(); it != newsStore.end(), x-- > 0; ++it)
        {
            newslist.push_back(it->second);
        }

        return newslist;
    }
};

