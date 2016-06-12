#include "test_util.h"
#include <random>

std::vector<Key> _random_keys(bool monotone, size_t count, Key min, Key max, int seed) {
    std::vector<Key> keys (count);

    if (monotone){
        keys[0] = min;
    }

    std::default_random_engine engine (seed);
    std::uniform_int_distribution<Key> distribution(min, max);
    distribution(engine); //first value always 0 ?!

    for (size_t i = (size_t)monotone; i < count; ++i){
        keys[i] = distribution(engine);
    }

    return keys;
}

std::vector<Key> random_keys(size_t count, Key min, Key max, int seed) {
    return _random_keys(false, count, min, max, seed);
}

std::vector<Key> random_keys_monotone(size_t count, Key min, Key max, int seed) {
    return _random_keys(true, count, min, max, seed);
}

