#include "ExtendedRadixHeap.h"

ExtendedRadixHeap::ExtendedRadixHeap() : buckets(new Bucket [BUCKETS]), cnt(0) {}

ExtendedRadixHeap::~ExtendedRadixHeap() {
    for (size_t i = 0; i < BUCKETS; ++i){
        Node * n = buckets[i].first;
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
        ++cnt;
        bucket_insert(bucket, x);
    } else {
        ExtendedRadixHeap * heap = new ExtendedRadixHeap();
        heap->insert(x, heap);
        heap->cnt += cnt;
        heap->bucket_insert(bucket, new Node(this));
        self = heap;
    }
}

Key ExtendedRadixHeap::delete_min() {
    --cnt;
    Node * min = buckets[0].first;
    Key old_min = key_min;
    if (min){
        bucket_remove(0);
    } else {
        for (size_t i = 1; i < BUCKETS; ++i){
            Bucket& b = buckets[i];
            if (b.first){
                min = b.first;
                Node * n = min->next;
                while (n){
                    if (n->key < min->key){
                        min = n;
                    }
                    n = n->next;
                }
                key_min = min->key;
                n = b.first;
                while (n){
                    Node * next = n->next;
                    if (n != min){
                        const size_t bucket = msd(key_min, n->key);
                        bucket_insert(bucket, n);
                    }
                    n = next;
                }
                b.first = nullptr;
                b.last = nullptr;
                break;
            }
        }
    }

    if (min->extended){
        const ExtendedRadixHeap * heap = min->extended;
        for (size_t i = 0; i < BUCKETS; ++i){
            Bucket& b = buckets[i], &hb = heap->buckets[i];
            b.last->next = hb.first;
            b.last = hb.last;
            hb.first = nullptr;
        }
        delete heap;
    }

    delete min;
    return old_min;
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
    const size_t bucket = msd(heap->key_min, key_min);
    min->bucket_insert(bucket, new Node(max));
    min->cnt += max->cnt;
    self = min;
}

void ExtendedRadixHeap::bucket_remove(size_t bucket) {
    Bucket& b = buckets[bucket];
    b.first = b.first->next;
    if (!b.first){
        b.last = nullptr;
    }
}

void ExtendedRadixHeap::bucket_insert(size_t bucket, Key key){
    Bucket& b = buckets[bucket];
    Node * n = new Node(key, b.first);
    if (!b.last){
        b.last = n;
    }
    b.first = n;
}

void ExtendedRadixHeap::bucket_insert(size_t bucket, Node *node) {
    Bucket& b = buckets[bucket];
    node->next = b.first;
    if (!b.last){
        b.last = node;
    }
    b.first = node;
}


ExtendedRadixHeap::Node::Node(Key key, ExtendedRadixHeap::Node *next) :
        key(key), next(next), extended(nullptr) { }

ExtendedRadixHeap::Node::Node(ExtendedRadixHeap *heap, ExtendedRadixHeap::Node *next) :
        key(heap->key_min), next(next), extended(heap){}

ExtendedRadixHeap::Node::~Node() {
    if (extended){
        delete extended;
    }
}





