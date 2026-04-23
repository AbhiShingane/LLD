#include<iostream>
#include<string>

using namespace std; 
static int counter = 0;


struct News
{
    std::string heading;
    std::string writer;
    std::string content;
    int pageNumber;
    string newsId;

    static int counter;
    public:
    News()
    {
        newsId = "";
        heading = "";
        writer = "";
        content = "";
        pageNumber = 0;
    }

    News(std::string h, std::string writername, std::string c, int pgnumber): heading(h), writer(writername),
                                            content(c), pageNumber(pgnumber)
                                            { 
                                                newsId = "NEWS" + to_string(counter++);
                                                
                                            }

};

int News::counter = 0;