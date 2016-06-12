#include <algorithm>
#include "RadixHeap.h"

void RadixHeap::insert(const Key x) {
    if (cnt++ == 0){
        key_min = x;
    }
    buckets[msd(x, key_min)].push(x);
}

Key RadixHeap::delete_min() {
    --cnt;
    Key old_min = key_min;
    if (buckets[0].length() > 0){
        buckets[0].pop();
    }
    if (buckets[0].length() == 0){
        for (size_t i = 1; i < BUCKETS; ++i){
            Stack & bucket = buckets[i];
            if (bucket.length() > 0){
                size_t min_j = 0;
                const size_t bucket_len = bucket.length();
                Key min = bucket[0], cur;
                for (size_t j = 1; j < bucket_len; ++j){
                    cur = bucket[j];
                    if (cur < min){
                        min = cur;
                        min_j = j;
                    }
                }

                key_min = min;
                buckets[0].push(min);
                for (size_t j = 0; j < bucket_len; ++j){
                    cur = bucket[j];
                    if (j != min_j){
                        buckets[msd(cur, key_min)].push(cur);
                    }
                }
                bucket.reset();

                break;
            }
        }
    }

    return old_min;
}


size_t RadixHeap::count() const {
    return cnt;
}


RadixHeap::Stack::Stack() : size(1), len(0), arr(new Key[1]){

}

RadixHeap::Stack::~Stack() {
    delete [] arr;
}

void RadixHeap::Stack::push(const Key x) {
    if (size == len){
        resize(2 * len);
    }
    arr[len++] = x;
}

void RadixHeap::Stack::pop() {
    --len;
}

Key RadixHeap::Stack::operator[](const size_t i) const {
    return arr[i];
}

size_t RadixHeap::Stack::length() const {
    return len;
}

void RadixHeap::Stack::resize(const size_t new_size) {
    Key * new_arr = new Key[new_size];
    std::copy(arr, arr + len, new_arr);
    delete [] arr;
    arr = new_arr;
    size = new_size;
}

void RadixHeap::Stack::reset() {
    len = 0;
}
















