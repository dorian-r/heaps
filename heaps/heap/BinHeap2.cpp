#include "BinHeap2.h"
#include <algorithm>
#include <iostream>

const size_t mod16 = ~((size_t)0) >> (8 * sizeof(size_t) - 4);

BinHeap2::BinHeap2(const size_t size) : size(size), cnt(0), arr(new Key [(size + 14) / 15 * 16]), last(0){}

BinHeap2::~BinHeap2() {
    delete [] arr;
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
    const size_t m = i & mod16, b = i / 16;
    if (m){
        return b * 16 + (m - 1) / 2;
    }
    const size_t pb = (b - 1) / 16;
    return 16 * pb + 6 + (b - 16 * pb + 1) / 2;
}

size_t BinHeap2::left(size_t i) {
    const size_t m = i & mod16, b = i / 16;
    if (m < 7){
        return b * 16 + m * 2 + 1;
    }
    return (b * 16 + (m - 7) * 2 + 1) * 16;
}

size_t BinHeap2::right(size_t i) {
    const size_t m = i & mod16, b = i / 16;
    if (m < 7){
        return b * 16 + m * 2 + 2;
    }
    return (b * 16 + (m - 7) * 2 + 2) * 16;
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
    return (cnt / 15) * 16 + cnt % 15;
}

bool BinHeap2::check_heap_invariant(size_t i) {
    bool ret = true;
    if (left(i) < last){
        ret &= arr[i] <= arr[left(i)];
        if (ret){
            ret &= check_heap_invariant(left(i));
        } else {
            std::cout << "inv " << i << std::endl;
            return false;
        }
    }
    if (right(i) < last){
        ret &= arr[i] <= arr[right(i)];
        if (ret){
            ret &= check_heap_invariant(right(i));
        } else {
            std::cout << "inv " << i << std::endl;
            return false;
        }
    }
    return ret;
}

void BinHeap2::print_heap(size_t i) {
    std::cout << i << ": " <<arr[i];
    if (left(i) < last){
        std::cout << " l " << arr[left(i)];
    }
    if (right(i) < last){
        std::cout << " r " << arr[right(i)];
    }
    std::cout << std::endl;
    if (left(i) < last){
        print_heap(left(i));
    }
    if (right(i) < last){
        print_heap(right(i));
    }
}

void BinHeap2::check(size_t i) {
    if (i < last){
        if (arr[i] > 999){
            std::cout << "." << i << std::endl;
        }
        check(left(i));
        check(right(i));
    }
}































