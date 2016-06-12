#include "gtest/gtest.h"
#include "test_util.h"
#include "iostream"
#include "BinHeap.h"
#include <algorithm>

template<typename T> void test_heap(T& heap, std::vector<Key> keys){
    for (const auto & key : keys){
        heap.insert(key);
    }
    std::sort(keys.begin(), keys.end());
    std::vector<Key> actual (keys.size());
    for (size_t i = 0; i < keys.size(); ++i){
        actual[i] = heap.delete_min();
    }
    EXPECT_EQ(keys, actual);
}

TEST(BinHeap, test_10){
    BinHeap heap (10);
    test_heap(heap, random_keys(10, 0, 50));
}

TEST(BinHeap, test_1000000){
    BinHeap heap (1000000);
    test_heap(heap, random_keys(1000000));
}

TEST(BinHeap, build_10){
    auto keys = random_keys(10, 0, 50);
    BinHeap * heap = BinHeap::build(&keys[0], 10);
    std::sort(keys.begin(), keys.end());
    std::vector<Key> actual (keys.size());
    for (size_t i = 0; i < keys.size(); ++i){
        actual[i] = heap->delete_min();
    }
    delete heap;
    EXPECT_EQ(keys, actual);
}

TEST(BinHeap, build_1000000){
    auto keys = random_keys(1000000);
    BinHeap * heap = BinHeap::build(&keys[0], 1000000);
    std::sort(keys.begin(), keys.end());
    std::vector<Key> actual (keys.size());
    for (size_t i = 0; i < keys.size(); ++i){
        actual[i] = heap->delete_min();
    }
    delete heap;
    EXPECT_EQ(keys, actual);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}