#include "BinHeap2.h"
#include <algorithm>
#include <iostream>
#include <memory>

const size_t mod16 = ~((size_t)0) >> (8 * sizeof(size_t) - 4);

const size_t modD = mod16; //modulus operator
const size_t D = 16; //size the of array slice where on block will be stored
const size_t S = D - 1; //number of nodes stored in one block
const size_t F = 7; //number of nodes in one block that are not leaves

const size_t alignment = 64;

BinHeap2::BinHeap2(const size_t size) : size(size), cnt(0), last(0){
    allocate(size);
}

BinHeap2::~BinHeap2() {
    delete [] ptr;
}

void BinHeap2::insert(const Key x) {
    if (cnt == size){
        resize(2 * size);
    }
    cnt++;
    arr[last] = x;
    heapify_up(last);
    last = last_idx();
}

Key BinHeap2::delete_min() {
    Key min = arr[0];
    cnt--;
    last = last_idx();
    arr[0] = arr[last];
    heapify_down(0);
    return min;
}

size_t BinHeap2::count() const {
    return cnt;
}

size_t BinHeap2::parent(size_t i) {
    const size_t m = i & modD, b = i / D;
    if (m){
        return b * D + (m - 1) / 2;
    }
    const size_t pb = (b - 1) / D;
    return D * pb + F - 1 + (b - D * pb + 1) / 2;
}

size_t BinHeap2::left(size_t i) {
    const size_t m = i & modD, b = i / D;
    if (m < F){
        return b * D + m * 2 + 1;
    }
    return (b * D + (m - F) * 2 + 1) * D;
}

size_t BinHeap2::right(size_t i) {
    const size_t m = i & modD, b = i / D;
    if (m < F){
        return b * D + m * 2 + 2;
    }
    return (b * D + (m - F) * 2 + 2) * D;
}

void BinHeap2::resize(size_t new_size) {
    Key * old_arr = arr, * old_ptr = ptr;
    allocate(new_size);
    std::copy(old_arr, old_arr + last_idx(), arr);
    delete [] old_ptr;
}


void BinHeap2::heapify_up(size_t i) {
    size_t par = parent(i);
    while (i > 0 && arr[par] > arr[i]){
        swap(arr, par, i);
        i = par;
        par = parent(i);
    }
}

void BinHeap2::heapify_down(size_t i) {
    size_t lc = left(i), rc = right(i);
    while (lc < last){
        size_t m = lc;
        if (rc < last && arr[rc] < arr[lc]){
            m = rc;
        }
        if (arr[i] <= arr[m]){
            return;
        }
        swap(arr, i, m);
        i = m;
        lc = left(i), rc = right(i);
    }
}

size_t BinHeap2::last_idx() {
    return (cnt / S) * D + cnt % S;
}

void BinHeap2::allocate(size_t size) {
    this->size = size;
    size_t sz = (size + S - 1) / S * D;
    size_t sp = sz + alignment;
    ptr = new Key [sp];
    void* a = (void*)ptr;
    align(alignment, sz, a, sp);
    arr = (Key*)a;
}































