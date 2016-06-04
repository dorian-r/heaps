#include "ExtendedRadixHeap.h"

ExtendedRadixHeap::ExtendedRadixHeap() : buckets(new Node* [BUCKETS]), cnt(0) {}

ExtendedRadixHeap::~ExtendedRadixHeap() {
    for (size_t i = 0; i < BUCKETS; ++i){
        Node * n = buckets[i];
        while (n){
            Node * old = n;
            n = old->next;
            delete old;
        }
    }
    delete [] buckets;
}

void ExtendedRadixHeap::insert(const Key x, ExtendedRadixHeap * & self) {
    if (cnt == 0){
        key_min = x;
    }
    size_t bucket = msd(x, key_min);
    if (key_min <= x){
        buckets[bucket] = new Node(x, buckets[bucket]);
    } else {
        ExtendedRadixHeap * heap = new ExtendedRadixHeap();
        heap->insert(x, heap);
        heap->cnt += cnt;
        heap->buckets[bucket] = new Node(this, heap->buckets[bucket]);
        self = heap;
    }
}

Key ExtendedRadixHeap::delete_min() {

    return 0;
}

size_t ExtendedRadixHeap::count() const {
    return cnt;
}

void ExtendedRadixHeap::merge(ExtendedRadixHeap *heap, ExtendedRadixHeap * & self) {
    ExtendedRadixHeap * min, * max;
    if (key_min > heap->key_min){
        min = heap, max = this;
    } else {
        min = this, max = heap;
    }
    size_t bucket = msd(heap->key_min, key_min);
    min->buckets[bucket] = new Node(max, min->buckets[bucket]);
    min->cnt += max->cnt;
    self = min;
}


ExtendedRadixHeap::Node::Node(const Key key, ExtendedRadixHeap::Node *next) :
        key(key), next(next), extended(nullptr) { }

ExtendedRadixHeap::Node::Node(const ExtendedRadixHeap *heap, ExtendedRadixHeap::Node *next) :
        key(heap->key_min), next(next), extended(heap){}

ExtendedRadixHeap::Node::~Node() {
    if (extended){
        delete extended;
    }
}





