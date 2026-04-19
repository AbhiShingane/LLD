#include<iostream>
#include<string>


struct News
{
    std::string heading;
    std::string writer;
    std::string content;
    int pageNumber;

    public:
    News()
    {
        heading = "";
        writer = "";
        content = "";
        pageNumber = 0;
    }

    News(std::string h, std::string writername, std::string c, int pgnumber): heading(h), writer(writername),
                                            content(c), pageNumber(pgnumber){}

};