#include<iostream>
#include<Block.h>
#include<MemoryAllocator.h>

using namespace std;

void rundemo(const char* label, MemoryAllocator::Strategy s)
{
    cout<<"Memory allocator: "<<endl;

    MemoryAllocator ma(1024);

    void *a = ma.allocate(64, s);
    void *b = ma.allocate(128, s);

    void *c = ma.allocate(32, s);
    ma.logMemoryBlocks();
    cout<<"Deallocating of node: "<<endl;
    ma.deallocate(b);

    ma.logMemoryBlocks();


    return;
}

int main()
{
    rundemo("FIRST FIT", MemoryAllocator::Strategy::FIRST);
    rundemo("BEST FIT", MemoryAllocator::Strategy::BEST);
    rundemo("NEXT FIT", MemoryAllocator::Strategy::NEXT);
    rundemo("WORST FIT", MemoryAllocator::Strategy::WORST);

    return;
}