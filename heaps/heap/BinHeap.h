#ifndef HEAPS_BINHEAP_H
#define HEAPS_BINHEAP_H

#include <cstddef>
#include "util.h"

class BinHeap {
public:
    BinHeap(const size_t size);
    ~BinHeap();
    void insert(const Key x);
    Key delete_min();
    size_t count() const;
    static BinHeap * build(Key * keys, size_t len);
private:
    Key * arr;
    size_t size, cnt;
    void resize(size_t new_size);
    void heapify_up(size_t i);
    void heapify_down(size_t i);
    static size_t parent(size_t i);
    static size_t left(size_t i);
    static size_t right(size_t i);
};


#endif //HEAPS_BINHEAP_H
