#include <iostream>
#include "test_util.h"
#include "Timer.h"
#include <util.h>
#include <BinHeap.h>
#include <type_traits>
#include <ExtendedRadixHeap.h>
#include <RadixHeap.h>

int64_t measure_bin_heap(const std::vector<Key> & keys, int repetitions){
    Timer timer;
    for (int r = 0; r < repetitions; ++r){
        BinHeap * heap = new BinHeap(keys.size());
        timer.start();
        for (size_t i = 0; i < keys.size(); ++i){
            heap->insert(keys[i]);
        }
        for (size_t i = 0; i < keys.size(); ++i){
            heap->delete_min();
        }
        timer.stop();
        delete heap;
    }
    std::cout << timer.average() << std::endl;
    return timer.average();
}

int64_t measure_bin_heap_build(std::vector<Key> & keys, int repetitions){
    Timer timer;
    for (int r = 0; r < repetitions; ++r){
        timer.start();
        BinHeap * heap = BinHeap::build(&keys[0], keys.size());
        for (size_t i = 0; i < keys.size(); ++i){
            heap->delete_min();
        }
        timer.stop();
        delete heap;
    }
    std::cout << timer.average() << std::endl;
    return timer.average();
}

int64_t measure_radix_heap(const std::vector<Key> & keys, int repetitions){
    Timer timer;
    for (int r = 0; r < repetitions; ++r){
        RadixHeap * heap = new RadixHeap;
        timer.start();
        for (size_t i = 0; i < keys.size(); ++i){
            heap->insert(keys[i]);
        }
        for (size_t i = 0; i < keys.size(); ++i){
            heap->delete_min();
        }
        timer.stop();
        delete heap;
    }
    std::cout << timer.average() << std::endl;
    return timer.average();
}

int64_t measure_extended_radix_heap(const std::vector<Key> & keys, int repetitions){
    Timer timer;
    for (int r = 0; r < repetitions; ++r){
        ExtendedRadixHeap * heap = new ExtendedRadixHeap;
        timer.start();
        for (size_t i = 0; i < keys.size(); ++i){
            heap->insert(keys[i], heap);
        }
        for (size_t i = 0; i < keys.size(); ++i){
            heap->delete_min();
        }
        timer.stop();
        delete heap;
    }
    std::cout << timer.average() << std::endl;
    return timer.average();
}

void test(bool monotone, int repetitions, size_t count){
    auto keys = random_keys(monotone, count);
    measure_bin_heap(keys, repetitions);
    //measure_bin_heap_build(keys, repetitions);
    if (monotone) {
        measure_radix_heap(keys, repetitions);
    }
    measure_extended_radix_heap(keys, repetitions);
}

int main(int argc, char **argv) {
    test(true, 1, 10000000);
}