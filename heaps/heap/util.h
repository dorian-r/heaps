#ifndef HEAPS_UTIL_H_H
#define HEAPS_UTIL_H_H

#include <cstdint>
#include <cstddef>

typedef uint32_t Key;

template<typename T>
inline void swap(T *a, size_t i, size_t j) {
    T tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

const size_t BUCKETS = sizeof(Key) * 8 + 1;

inline size_t msd(const Key a, const Key b) {
    const Key x = a ^ b;
    return x == 0 ? 0u : 64 - __builtin_clzll(x);
}

//this function was missing from std in gcc 4.9
inline void *align(size_t __alignment, size_t __size, void *&__ptr, size_t &__space) {
    const size_t __diff = __alignment -
                          +reinterpret_cast<uintptr_t>(__ptr) % __alignment;
    if (__diff + __size >= __space)
        return nullptr;
    else {
        __space -= __diff;
        __ptr = static_cast<char *>(__ptr) + __diff;
        return __ptr;
    }
}


#endif //HEAPS_UTIL_H_H
