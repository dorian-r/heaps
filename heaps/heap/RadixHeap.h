#ifndef HEAPS_RADIXHEAP_H
#define HEAPS_RADIXHEAP_H


#include <cstddef>
#include "util.h"
#include "Stack.h"

class RadixHeap {
public:
    RadixHeap(size_t size=0){}
    void insert(const Key x);
    Key delete_min();
    size_t count() const;

private:
    Stack<Key> buckets [BUCKETS];
    Key key_min;
    size_t cnt = 0;
};


#endif //HEAPS_RADIXHEAP_H
