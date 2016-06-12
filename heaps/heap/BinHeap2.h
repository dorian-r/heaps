#ifndef HEAPS_BinHeap2_H
#define HEAPS_BinHeap2_H

#include <cstddef>
#include "util.h"

class BinHeap2 {
public:
    BinHeap2(const size_t size);
    ~BinHeap2();
    void insert(const Key x);
    Key delete_min();
    size_t count() const;
private:
    Key * arr;
    size_t size, cnt, last;
    void resize(size_t new_size);
    void heapify_up(size_t i);
    void heapify_down(size_t i);
    static size_t parent(size_t i);
    static size_t left(size_t i);
    static size_t right(size_t i);
    size_t last_idx();
};


#endif //HEAPS_BinHeap2_H
