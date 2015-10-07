#include <stdexcept>
#include <string>
#include <cstddef>

#include <set>
#include <list>
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

struct Info {
        size_t it;
        size_t size;
        Info(size_t i, size_t sz) {it = i; size = sz;}
    };

class Pointer {
private:

public:
    bool isEmpty;
    static std::list <Info> pList;
    std::list <Info>::iterator info;
    void * base;
    Pointer() {isEmpty = 1;/*(*info).it = 0;base = 0;(*info).size = 0;*/}
    ~Pointer(){}
    Pointer(size_t l, void * b, size_t sz) ;
    void *get() ;
    void clear();
};

//Pointer pjb;


class Allocator {
private:
    size_t size;
    void * base;
    char * used;

public:
    Allocator(void *base, size_t size);

    Pointer alloc(size_t);
    void realloc(Pointer &p, size_t N);
    void free(Pointer &p);

    void defrag();

    void printUsed();
    void print();
    std::string dump() { return ""; }
};

