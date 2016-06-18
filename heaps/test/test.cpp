#include "gtest/gtest.h"
#include "test_util.h"
#include "BinHeap.h"
#include "RadixHeap.h"
#include "ExtendedRadixHeap.h"
#include "ExtendedRadixHeap2.h"
#include "BinHeap2.h"
#include <algorithm>

typedef ::testing::Types<BinHeap, ExtRadixHeap, ExtRadixHeap2> NonMonotoneHeaps;
typedef ::testing::Types<RadixHeap, ExtRadixHeap, ExtRadixHeap2> MonotoneHeaps;

template <typename T> class HeapTestNonMonotone : public ::testing::Test { };
template <typename T> class HeapTestMonotone : public ::testing::Test { };

template<typename T> void test_heap_delete(T& heap, std::vector<Key>& keys){
    std::sort(keys.begin(), keys.end());
    std::vector<Key> actual (keys.size());
    for (size_t i = 0; i < keys.size(); ++i){
        actual[i] = heap.delete_min();
    }
    EXPECT_EQ(keys, actual);
}

template<typename T> void test_heap(std::vector<Key> keys){
    T heap (keys.size());
    for (const auto & key : keys){
        heap.insert(key);
    }
    test_heap_delete(heap, keys);
}

TYPED_TEST_CASE(HeapTestNonMonotone, NonMonotoneHeaps);
TYPED_TEST_CASE(HeapTestMonotone, MonotoneHeaps);

TYPED_TEST(HeapTestNonMonotone, test_10){
    test_heap<TypeParam>(random_keys(false, 10, 0, 50));
}

TYPED_TEST(HeapTestNonMonotone, test_1000000){
    test_heap<TypeParam>(random_keys(false, 1000000));
}

TYPED_TEST(HeapTestMonotone, test_10){
    test_heap<TypeParam>(random_keys(true, 10, 0, 50));
}

//TEST(erh, test_10){
//    test_heap<ExtRadixHeap2>({2, 3, 0, 1});
//}

TYPED_TEST(HeapTestMonotone, test_1000000){
    test_heap<TypeParam>(random_keys(true, 1000000));
}

TEST(BinHeap, build_10){
    auto keys = random_keys(false, 10, 0, 50);
    BinHeap * heap = BinHeap::build(&keys[0], 10);
    test_heap_delete(*heap, keys);
    delete heap;
}

TEST(BinHeap, build_1000000){
    auto keys = random_keys(false, 1000000);
    BinHeap * heap = BinHeap::build(&keys[0], 1000000);
    test_heap_delete(*heap, keys);
    delete heap;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}