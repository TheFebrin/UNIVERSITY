#include <stdexcept>
#include <stdio.h>

void* operator new(size_t size, int line)
{
    printf("Allocate %u bytes on line %d\n", size, line);
    return operator new(size);
}

class Obj {
public:
    Obj(int n);
private:
    int _n;
};

Obj::Obj(int n) : _n(n)
{
    if (n == 0) {
        throw std::runtime_error("0 not allowed");
    }
}

int main()
{
    try {
        Obj* p = new(__LINE__) Obj(0);
        delete p;
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}
