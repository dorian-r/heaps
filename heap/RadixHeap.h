#ifndef HEAPS_RADIXHEAP_H
#define HEAPS_RADIXHEAP_H


#include <cstddef>
#include "util.h"

class RadixHeap {
public:
    RadixHeap();
    ~RadixHeap();
    void insert(const Key x);
    Key delete_min();
    size_t count() const;

private:
    class Stack {
    public:
        Stack();
        ~Stack();
        void push(const Key x);
        Key pop();
        Key operator[](const size_t i) const;
        size_t length() const;
        void reset();
    private:
        void resize(const size_t new_size);
        size_t size, len;
        Key * arr;
    };

    Stack * buckets;
    Key key_min;
    size_t cnt;
};


#endif //HEAPS_RADIXHEAP_H