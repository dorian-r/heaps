#include <iostream>
#include "test_util.h"
#include "Timer.h"
#include "BinHeap.h"
#include "BinHeap2.h"
#include "ExtendedRadixHeap.h"
#include "RadixHeap.h"
#include "ExtendedRadixHeap2.h"

template <typename T> int64_t measure_heap(const std::vector<Key> & keys, int repetitions){
    Timer timer;
    for (int r = 0; r < repetitions + 1; ++r){
        T * heap = new T(keys.size());
        timer.start();
        for (size_t i = 0; i < keys.size(); ++i){
            heap->insert(keys[i]);
        }
        for (size_t i = 0; i < keys.size(); ++i){
            heap->delete_min();
        }
        timer.stop();
        if (r == 0){
            timer.reset();
        }
        delete heap;
    }
    std::cout << timer.average() << std::endl;
    return timer.average();
}

void test(bool monotone, int repetitions, size_t count){
    auto keys = random_keys(monotone, count);
    measure_heap<BinHeap>(keys, repetitions);
    if (monotone) {
        measure_heap<RadixHeap>(keys, repetitions);
    }
    measure_heap<ExtRadixHeap>(keys, repetitions);
    measure_heap<ExtRadixHeap2>(keys, repetitions);
}

int main(int argc, char **argv) {
    test(false, 1, 10000000);
}