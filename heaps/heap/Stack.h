#ifndef HEAPS_STACK_H
#define HEAPS_STACK_H


#include <cstddef>
#include <algorithm>
#include <iostream>

template <typename T> class Stack {
public:
    Stack() : size(1), len(0), arr(new T[1]){}
    ~Stack() { delete[] arr; }
    void push(const T x) {
        if (size == len){
            resize(2 * len);
        }
        arr[len++] = x;
    }
    T pop() {
        T ret = arr[--len];
#ifdef SHRINK
        if (4 * size < len && size > min_shrink){
            resize(2 * size);
        }
#endif
        return ret;
    }
    T operator[](const size_t i) const { return arr[i]; }
    size_t length() const { return len; };
    void reset(size_t max_size) {
        len = 0;
#ifdef SHRINK
        max_size = std::max(min_shrink, max_size);
        if (size > max_size){
            delete[] arr;
            arr = new T[max_size];
            size = max_size;
        }
#endif
    }
    void resize(const size_t new_size) {
        T * new_arr = new T[new_size];
        std::copy(arr, arr + len, new_arr);
        delete [] arr;
        arr = new_arr;
        size = new_size;
    };
private:
    size_t size, len;
    T * arr;
    static const size_t min_shrink;
};

template<typename T> const size_t Stack<T>::min_shrink = 8;

#endif //HEAPS_STACK_H
