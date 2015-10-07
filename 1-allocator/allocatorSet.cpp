#include "allocator.h"

bool operator < (Pointer a, Pointer b)
{
    return a.it < b.it;
}


Allocator::Allocator(void *base, size_t size)
{
    used = (char *)malloc(size);
    for (int i = 0; i < size; ++i)
        used[i] = 0;
    this->base = base;
    this->size = size;
}

Pointer Allocator::alloc(size_t N)
{
    int flag = 1, it = 0;
    for (int i = 0; i < size && flag; ++i)
    {
        if (used[i] == 0)
        {
            it = i;
            int cnt = 0;
            for (i; i < size && flag && cnt < N; ++i)
                cnt++;
            if (cnt == N)
            {
                --i;
                while (i >= it)
                {
                    used[i] = -1;
                    --i;
                }
                Pointer a = Pointer( it, base, N );

                ptrs.insert(a);
                return a;
            }
        }
    }
    throw AllocError(AllocErrorType::NoMemory, "MemIsOver");
}

void Allocator::free(Pointer &p)
{
    for (int i = 0; i < p.size; ++i)
    {
        used[p.it + i] = 0;
    }
    ptrs.erase(p);
    p.clear();
    return;
}

void Allocator::defrag()
{
    //for (auto it = ptrs.begin(); it != ptrs.end(); ++it)
    //    printf("%lld ", (long long)it->it);
    //printf("\n");

    std::set <Pointer> p;
    int last = 0;
    for (auto it = ptrs.begin(); it != ptrs.end(); ++it)
    {
        //std::cerr << 1 ;
        int i;
        for (i = 0; i < it->size; ++i)
        {
            ((char*)base)[last + i] = ((char*)base)[it->it + i];
            used[it->it + i] = 0;
            used[last + i] = -1;
            if (last > it->it)
                printf("FFAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIIIIIIILLLLLLL");
        }

        Pointer b = *it;
        b.it = last;
        last += i;
        //std::cerr << last << " ";
        p.insert(b);
        //print();
    }
     //std::cerr << std::endl;
    ptrs.clear();
    ptrs = p;
    p = std::set <Pointer> ();
}

void Allocator::print()
{
    /*for (int i = 0; i < 40; ++i)
    {
        for (int i2 = 0; i2 < 35; ++i2)
            //printf("%.2x ", ((unsigned char * )base)[i * 40 + i2]);
            printf(((int)used[i * 20 + i2] == 0 ? " 0" : "-1"));
        printf("\n");
        //std::cout << std::endl;
    }

    printf("\n");*/
    int cnt = 0, last = used[0], st = 0;
    for (int i = 0; i < size; ++i)
    {
        if (last != used[i])
        {
            printf("{%d|%.5d|%.5d} ", last, cnt, st);
            last = used[i];
            cnt = 1;
            st = i;
        }
        else
            cnt++;
    }
    printf("{%d|%.5d|%.5d} \n\n", last, cnt,st);
}

