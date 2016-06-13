#ifndef HEAPS_EXTENDEDRADIXHEAP2_H
#define HEAPS_EXTENDEDRADIXHEAP2_H

#include "util.h"
#include "ExtendedRadixHeapWrapper.h"
#include "Stack.h"

class ExtendedRadixHeap2 {
public:
    ~ExtendedRadixHeap2();
    void insert(const Key x, ExtendedRadixHeap2*& self);
    Key delete_min();
    size_t count() const;
private:
    struct Item {
        Item() : key(0), extended(nullptr) {}
        Item(Key key) : key(key), extended(nullptr) {}
        Item(ExtendedRadixHeap2 * extended) : key(extended->key_min), extended(extended) {}
        ExtendedRadixHeap2 * extended;
        Key key;
    };
    struct LazyBucket {
        Stack<Item> stack;
        LazyBucket * next = nullptr;
    };

    void bucket_insert(const size_t bucket, Item item);
    Item bucket_pop(const size_t bucket);
    void join(ExtendedRadixHeap2 * heap);
    void redistribute(size_t bucket);

    LazyBucket * buckets [BUCKETS] = {};
    LazyBucket * last_bucket [BUCKETS] = {};
    Key key_min;
    size_t cnt = 0;
};

typedef ExtendedRadixHeapWrapper<ExtendedRadixHeap2> ExtRadixHeap2;

#endif //HEAPS_EXTENDEDRADIXHEAP2_H
