#ifndef HEAPS_EXTENDEDRADIXHEAP_H
#define HEAPS_EXTENDEDRADIXHEAP_H


#include <cstddef>
#include "util.h"

class ExtendedRadixHeap {
public:
    ExtendedRadixHeap();
    ~ExtendedRadixHeap();
    void insert(const Key x, ExtendedRadixHeap * & self);
    Key delete_min();
    size_t count() const;
    void merge(ExtendedRadixHeap * heap, ExtendedRadixHeap * & self);

private:
    struct Node {
        Node (Key key, Node * next = nullptr);
        Node (ExtendedRadixHeap * heap, Node * next = nullptr);
        ~Node();

        const ExtendedRadixHeap * extended;
        Node * next;
        const Key key;
    };

    struct Bucket{
        Node * first, * last;
    };

    void bucket_insert(size_t bucket, Key key);
    void bucket_insert(size_t bucket, Node * node);
    void bucket_remove(size_t bucket);

    Bucket * buckets;
    Key key_min;
    size_t cnt;
};


#endif //HEAPS_EXTENDEDRADIXHEAP_H
