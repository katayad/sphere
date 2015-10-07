#include "allocator.h"
#include <cstdio>
#include <cstring>

std::list <Info> Pointer::pList;

bool operator < (Info a, Info b)
{
    return a.it < b.it;
}

Pointer::Pointer(size_t l, void * b, size_t sz)
{
    pList.push_back(Info(l, sz));
    info = pList.end();
    info--;
    base = b;
    isEmpty = 0;
}

void * Pointer::get()
{
    if (isEmpty)
        return nullptr;
    return (void *)((ptrdiff_t)base + (*this->info).it);
}

void Pointer::clear()
{
    isEmpty = 1;
}

Allocator::Allocator(void *base, size_t size)
{
    Pointer::pList.clear();
    memset(base, 0, size);
    used = (char *)malloc(size);
    for (int i = 0; i < size; ++i)
        used[i] = 0;
    this->base = base;
    this->size = size;
}

Pointer Allocator::alloc(size_t N)
{
    //std::cerr << N << std::endl;
    //print();
    //printUsed();
    //defrag();
    //printUsed();
    //print();
    int flag = 1, it = 0;
    for (int i = 0; i < size && flag; ++i)
    {
        if (used[i] == 0)
        {
            it = i;
            int cnt = 0;
            for (i; i < size && flag && used[i] == 0 && cnt < N; ++i)
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
                //std::cerr << N << std::endl;
                //std::cerr << (*a.info).size << std::endl;
                return a;
            }
        }
    }
    throw AllocError(AllocErrorType::NoMemory, "MemIsOver");
}

void Allocator::realloc(Pointer & p, size_t N)
{
    if (p.isEmpty)
    {
        p = alloc(N);
        return;
    }
    if (N < p.info->size)
    {
        for (int i = N; i < p.info->size; ++i)
        {
            used[p.info->it + i] = 0;
        }
        p.info->size = N;
        return;
    }
    //std::cerr << "reallocing...\n";
    //defrag();
    size_t sz = p.info->size;
    char * a = new char[sz];
        for (int i = 0; i < sz; ++i) a[i] = ((char *)base)[p.info->it + i];
        this->free(p);
        defrag();
        p = alloc(N);
        for (int i = 0; i < sz; ++i) ((char *)base)[p.info->it + i] = a[i];

    delete a;
}

void Allocator::free(Pointer &p)
{
    for (int i = 0; i < (*p.info).size; ++i)
    {
        used[(*p.info).it + i] = 0;
    }
    //std::cerr << (*p.info).it << std::endl;
    Pointer::pList.erase(p.info);
    p.clear();
    //free(p);

    return;
}

void Allocator::defrag()
{
    int last = 0;
    Pointer::pList.sort();
    //std::cerr << "DEFRUUUUUG\n";
    for (auto it = Pointer::pList.begin(); it != Pointer::pList.end(); ++it)
    {
        //std::cerr << "d" ;
        int i;
        for (i = 0; i < it->size; ++i)
        {
            ((char*)base)[last + i] = ((char*)base)[it->it + i];
            used[it->it + i] = 0;
            used[last + i] = -1;
        }

        //Pointer b = *it;
        it->it = last;
        last += i;
    }
     //std::cerr << std::endl;
}

void Allocator::print()
{
    for (int i = 0; i < 10; ++i)
    {
        printf("%.3d ", i * 40);
        for (int i2 = 0; i2 < 40; ++i2)
            printf("%.2x ", ((unsigned char * )base)[i * 40 + i2]);
            //printf(((int)used[i * 20 + i2] == 0 ? " 0" : "-1"));
        printf("\n");
        //std::cout << std::endl;
    }

    printf("\n");
}

void Allocator::printUsed()
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

