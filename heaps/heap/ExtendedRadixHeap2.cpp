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

    if (bucket_empty(0)){
        for (size_t i = 1; i < BUCKETS; ++i){
            if (!bucket_empty(i)){
                redistribute(i);
                break;
            }
        }
    }

    return old_min;
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

ExtendedRadixHeap2::Item ExtendedRadixHeap2::bucket_pop(const size_t bucket) {
    auto b = buckets[bucket];
    Item item;
    if (b->stack.length() > 0){
        item = b->stack.pop();
    } else {
        item = b->next->stack.pop();
        if (b->next->stack.length() == 0){
            auto tmp = b->next;
            b->next = b->next->next;
            if (b->next == nullptr){
                last_bucket[bucket] = b;
            }
            delete tmp;
        }
    }
    return item;
}

void ExtendedRadixHeap2::join(ExtendedRadixHeap2 *heap) {
    for (size_t i = 0; i < BUCKETS; ++i){
        if (!heap->bucket_empty(i)){
            auto & last = last_bucket[i];
            auto & bucket = heap->buckets[i];
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
        if (b == buckets[0]){
            b->stack.reset();
        } else {
            delete tmp;
        }
    }
    buckets[bucket] = nullptr;
    last_bucket[bucket] = nullptr;
}

bool ExtendedRadixHeap2::bucket_empty(const size_t bucket) {
    auto b = buckets[bucket];
    return b == nullptr || (b->stack.length() == 0 && b->next == nullptr);
}

















