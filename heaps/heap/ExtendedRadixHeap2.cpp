#include "ExtendedRadixHeap2.h"

ExtendedRadixHeap2::~ExtendedRadixHeap2() {
    for (size_t i = 0; i < BUCKETS; ++i){
        LazyBucket * bucket = buckets[i];
        while (bucket != nullptr){
            LazyBucket * tmp = bucket;
            bucket = bucket->next;
            delete tmp;
        }
    }
}

void ExtendedRadixHeap2::insert(const Key x, ExtendedRadixHeap2 *&self) {
    if (cnt == 0){
        key_min = x;
    }
    size_t bucket = msd(x, key_min);
    if (key_min <= x){
        ++cnt;
        bucket_insert(bucket, x);
    } else {
        ExtendedRadixHeap2 * heap = new ExtendedRadixHeap2();
        heap->insert(x, heap);
        heap->cnt += cnt;
        heap->bucket_insert(bucket, this);
        self = heap;
    }
}

Key ExtendedRadixHeap2::delete_min() {
    --cnt;
    Item min = bucket_pop(0);
    while (min.extended){
        join(min.extended);
        min = bucket_pop(0);
    }
    Key old_min = key_min;

    if (buckets[0] == nullptr){
        for (size_t i = 0; i < BUCKETS; ++i){
            if (buckets[i] != nullptr){
                redistribute(i);
                break;
            }
        }
    }

    return key_min;
}

size_t ExtendedRadixHeap2::count() const {
    return cnt;
}

void ExtendedRadixHeap2::bucket_insert(const size_t bucket, const Item item) {
    auto & b = buckets[bucket];
    if (b == nullptr){
        b = new LazyBucket;
        last_bucket[bucket] = b;
    }
    b->stack.push(item);
}

Item ExtendedRadixHeap2::bucket_pop(const size_t bucket) {
    auto & b = buckets[bucket];
    const Item item = b->stack.pop();
    if (b->stack.length() == 0){
        auto tmp = b;
        b = b->next;
        delete tmp;
    }
    if (b == nullptr){
        last_bucket[bucket] = nullptr;
    }
    return item;
}

void ExtendedRadixHeap2::join(ExtendedRadixHeap2 *heap) {
    for (size_t i = 0; i < BUCKETS; ++i){
        auto & bucket = heap->buckets[i];
        if (bucket != nullptr){
            auto & last = last_bucket[i];
            if (last == nullptr){
                buckets[i] = bucket;
            } else {
                last->next = bucket;
            }
            last = heap->last_bucket[i];
            bucket = nullptr;
        }
    }
    delete heap;
}

void ExtendedRadixHeap2::redistribute(size_t bucket) {
    auto b = buckets[bucket];
    key_min = b->stack[0].key;
    while (b){
        for (size_t i = 0; i < b->stack.length(); ++i){
            Key key = b->stack[i].key;
            if (key < key_min){
                key_min = key;
            }
        }
        b = b->next;
    }
    b = buckets[bucket];
    while (b){
        for (size_t i = 0; i < b->stack.length(); ++i){
            Item item = b->stack[i];
            bucket_insert(msd(key_min, item.key), item);
        }
        auto tmp = b;
        b = b->next;
        delete b;
    }
    buckets[bucket] = nullptr;
    last_bucket[bucket] = nullptr;
}















