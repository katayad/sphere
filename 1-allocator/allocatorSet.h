#include <stdexcept>
#include <string>
#include <cstddef>
#include <set>
#include <iostream>
#include <algorithm>

enum class AllocErrorType {
    InvalidFree,
    NoMemory,
};

class AllocError: std::runtime_error {
private:
    AllocErrorType type;

public:
    AllocError(AllocErrorType _type, std::string message):
            runtime_error(message),
            type(_type)
    {}

    AllocErrorType getType() const { return type; }
};

class Allocator;

class Pointer {
private:

public:
    size_t it;
    void * base;
    size_t size;
    Pointer() {it = 0;base = 0;size = 0;}
    Pointer(size_t l, void * b, size_t sz) {it = l;base = b;size = sz;  }
    void clear(){it = 0;size = 0;base = 0;}
    void *get() const { return (void *)((ptrdiff_t)base + it); }
};

class Allocator {
private:
    size_t size;
    void * base;
    char * used;

public:
    std::set <Pointer> ptrs;
    Allocator(void *base, size_t size);

    Pointer alloc(size_t);
    void realloc(Pointer &p, size_t N) {}
    void free(Pointer &p);

    void defrag();

    void print();
    std::string dump() { return ""; }
};

