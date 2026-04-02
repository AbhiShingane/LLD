#include <iostream>
#include <algorithm>

using namespace std;

struct Suggestion
{
    public:
    std::string term;
    int frequencey;
    int score;

    bool operator>(const Suggestion& other) {return score > other.score;}
    bool operator<(const Suggestion& other) {return score < other.score;} 

};