#include <iostream>

struct Block
{
    std::size_t size;
    bool IsFree;
    Block *next;

};