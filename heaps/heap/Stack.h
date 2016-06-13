#ifndef HEAPS_STACK_H
#define HEAPS_STACK_H


#include <cstddef>
#include <algorithm>

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
    void del() { --len; }
    T pop() { return arr[--len]; }
    T operator[](const size_t i) const { return arr[i]; }
    size_t length() const { return len; };
    void reset() {len = 0;}
private:
    void resize(const size_t new_size) {
        T * new_arr = new T[new_size];
        std::copy(arr, arr + len, new_arr);
        delete [] arr;
        arr = new_arr;
        size = new_size;
    };
    size_t size, len;
    T * arr;
};

#endif //HEAPS_STACK_H
