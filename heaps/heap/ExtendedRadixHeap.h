#ifndef HEAPS_EXTENDEDRADIXHEAP_H
#define HEAPS_EXTENDEDRADIXHEAP_H

#include <cstddef>
#include "util.h"

class ExtendedRadixHeap {
public:
    ~ExtendedRadixHeap();
    void insert(const Key x, ExtendedRadixHeap*& self);
    Key delete_min();
    size_t count() const;
    void merge(ExtendedRadixHeap * heap, ExtendedRadixHeap * & self);

private:
    struct Node {
        Node (Key key, Node * next = nullptr);
        Node (ExtendedRadixHeap * heap, Node * next = nullptr);
        ~Node();

        ExtendedRadixHeap * extended;
        Node * next;
        const Key key;
    };

    struct Bucket{
        Node * first = nullptr, * last = nullptr;
    };

    void bucket_insert(size_t bucket, Key key);
    void bucket_insert(size_t bucket, Node * node);
    void bucket_remove(size_t bucket);

    Bucket buckets [BUCKETS];
    Key key_min;
    size_t cnt = 0;
};


#endif //HEAPS_EXTENDEDRADIXHEAP_H
