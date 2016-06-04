#include "BinHeap.h"
#include <algorithm>

BinHeap::BinHeap(const size_t size) : size(size), cnt(0), arr(new Key [size]){}

BinHeap::~BinHeap() {
    delete [] arr;
}

void BinHeap::insert(const Key x) {
    if (cnt == size){
        resize(2 * size);
    }
    arr[cnt] = x;
    heapify_up(cnt++);
}

Key BinHeap::delete_min() {
    Key min = arr[0];
    arr[0] = arr[--cnt];
    heapify_down(0);
    return min;
}

size_t BinHeap::count() const {
    return cnt;
}

size_t BinHeap::parent(size_t i) {
    return (i - 1) / 2;
}

size_t BinHeap::left(size_t i) {
    return 2 * i + 1;
}

size_t BinHeap::right(size_t i) {
    return 2 * i + 2;
}

void BinHeap::resize(size_t new_size) {
    Key * new_arr = new Key[new_size];
    std::copy(arr, arr + cnt, new_arr);
    delete [] arr;
    arr = new_arr;
    size = new_size;
}

BinHeap * BinHeap::build(Key *keys, size_t len) {
    BinHeap * heap  = new BinHeap(len);
    std::copy(keys, keys + len, heap->arr);
    for (size_t i = len / 2; i > 0; --i){
        heap->heapify_down(i - 1);
    }
    return heap;
}

void BinHeap::heapify_up(size_t i) {
    size_t par = parent(i);
    while (i > 0 && arr[par] > arr[i]){
        swap(arr, par, i);
        i = par;
        par = parent(i);
    }
}

void BinHeap::heapify_down(size_t i) {
    size_t lc = left(i), rc = right(i);
    while (lc < cnt){
        size_t m = lc;
        if (rc < cnt && arr[rc] < arr[lc]){
            m = rc;
        }
        if (arr[i] <= arr[m]){
            return;
        }
        swap(arr, i, m);
        i = m;
    }
}























