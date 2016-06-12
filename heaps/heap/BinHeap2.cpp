#include "BinHeap2.h"
#include <algorithm>

const size_t mod16 = ~((size_t)0) >> (8 * sizeof(size_t) - 4);

BinHeap2::BinHeap2(const size_t size) : size(size), cnt(0), arr(new Key [(size + 14) / 15 * 16]){}

BinHeap2::~BinHeap2() {
    delete [] arr;
}

void BinHeap2::insert(const Key x) {
    if (cnt == size){
        resize(2 * size);
    }
    cnt++;
    last = last_idx();
    arr[last] = x;
    heapify_up(last);
}

Key BinHeap2::delete_min() {
    Key min = arr[0];
    arr[0] = arr[last];
    cnt--;
    last = last_idx();
    heapify_down(0);
    return min;
}

size_t BinHeap2::count() const {
    return cnt;
}

/*size_t BinHeap2::parent(size_t i) {
    const size_t m = i & mod16, b = i >> 4;
    if (i){
        return (b << 4) + ((m - 1) >> 1);
    }
    return b + 6;
}

size_t BinHeap2::left(size_t i) {
    const size_t m = i & mod16, b = i >> 4;
    if (m < 7){
        return (b << 4) + (m << 1) + 1;
    }
    return ((b << 4) + ((m - 7) << 2) + 1) << 4;
}

size_t BinHeap2::right(size_t i) {
    const size_t m = i & mod16, b = i >> 4;
    if (m < 7){
        return (b << 4) + (m << 1) + 2;
    }
    return ((b << 4) + ((m - 7) << 1) + 2) << 4;
}*/

size_t BinHeap2::parent(size_t i) {
    const size_t m = i & mod16, b = i / 16;
    if (m){
        return b * 16 + (m - 1) / 2;
    }
    return b + 6;
}

size_t BinHeap2::left(size_t i) {
    const size_t m = i & mod16, b = i / 16;
    if (m < 7){
        return b * 16 + m * 2 + 1;
    }
    return (b * 4 + (m - 7) * 2 + 1) * 16;
}

size_t BinHeap2::right(size_t i) {
    const size_t m = i & mod16, b = i / 16;
    if (m < 7){
        return b * 16 + m * 2 + 2;
    }
    return (b * 4 + (m - 7) * 2 + 2) * 16;
}

void BinHeap2::resize(size_t new_size) {
    Key * new_arr = new Key[new_size];
    std::copy(arr, arr + cnt, new_arr);
    delete [] arr;
    arr = new_arr;
    size = new_size;
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
    size_t lc = left(i), rc = right(i), l = last_idx();
    while (lc <= l){
        size_t m = lc;
        if (rc < cnt && arr[rc] < arr[lc]){
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
    return (cnt / 15) * 16 + cnt % 15;
}

























