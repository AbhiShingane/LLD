#include<iostream>
#include<cstring>
#include<Block.h>
#include<algorithm>

using namespace std;

class MemoryAllocator
{
    char *pool;
    size_t poolsize;
    Block *head;
    Block *nextFitPtr;


    Block* raw(char *p)
    {
        return reinterpret_cast<Block*>(p);
    }

    bool canfit(Block *b, size_t sz)
    {
        if(b->IsFree && b->size >= sz)
            return true;
        else
            return false;
    }


    char *data(Block *b)
    {
        return reinterpret_cast<char *>(b) + sizeof(Block);
    }

    //Merge adjecent free blocks
    void coalesce()
    {
        Block *ptr = head;
        while(ptr && ptr->next)
        {
            if(ptr->IsFree && ptr->next->IsFree)
            {
                ptr->size += sizeof(Block) + ptr->next->size;
                ptr = ptr->next->next;
            }
            else
                ptr = ptr->next;
        }

        return;
    }

    //Split the block if leftover is large enough
    void split(Block* b, size_t sz)
    {
        if(b->size < (sz + sizeof(Block) + 8)) return ;
        
        Block* newblk = raw(data(b) + sz);
        newblk->size = b->size - sz - sizeof(Block);
        newblk->IsFree = true;
        newblk->next = b->next;
        b->size = sz;
        b->next = newblk;
        
        return;
    }

    public:
    enum Strategy {FIRST, NEXT, BEST, WORST};

    MemoryAllocator(size_t sz) : poolsize(sz)
    {
        pool = new char[sz];
        head = raw(pool);

        head->size = sz - sizeof(Block);
        head->IsFree = true;
        head->next = nullptr;
        nextFitPtr = head;
    }

    ~MemoryAllocator() { delete[] pool;}
    
    void* allocate(size_t sz, Strategy s)
    {
        coalesce();
        Block *chosen = nullptr;

        if(s == FIRST)
        {
            Block *b = head;
            while(b)
            {
                if(canfit(b, sz))
                {
                    chosen = b;
                    break;
                }
                b = b->next;
            }
        }
        else if(s == NEXT)
        {
            Block *start = nextFitPtr;
            Block *b = start;

            do
            {
                if(!b) 
                    b = head;

                if(canfit(b, sz))
                {
                    chosen = b;
                    nextFitPtr = b->next;
                    break;
                }
                b = b->next;

            } while (b != start);
            
        }
        else if(s == BEST)
        {
            Block *b = head;
            while(b)
            {
                if(canfit(b, sz) && (!chosen || b->size < chosen->size))
                    chosen = b;

                b = b->next;
            }
        }
        else
        {
            Block *b = head;
            while(b)
            {
                if(canfit(b, sz) && (!chosen || b->size > chosen->size))
                    chosen = b;

                b = b->next;
            }
        }

        if(!chosen)
            cout<<"allocation failed"<<endl;
        
        split(chosen, sz);

        chosen->IsFree = false;
        return data(chosen);
    }

    void deallocate(void* ptr)
    {
        if(!ptr) nullptr;

        Block *b = raw(static_cast<char *>(ptr) - sizeof(Block));
        b->IsFree = true;
        nextFitPtr = nullptr;
        coalesce();
    }

    void logMemoryBlocks()
    {
        Block *ptr = head;
        int count = 1;
        while(ptr)
        {
            cout<<"BLOCK[ "<<count <<" ] size = "<ptr->size<<"BLOCK STATUS: "<<(ptr->IsFree ? "FREE" : "USED")<<endl;

            ptr = ptr->next;
        }

        return;
    }

};