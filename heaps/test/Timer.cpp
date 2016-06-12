#include "Timer.h"

void Timer::start() {
    start_time = Clock::now();
}

void Timer::stop() {
    auto stop_time = Clock::now();
    measurements.push_back(stop_time - start_time);
}

int64_t Timer::average() const {
    auto sum = measurements[0];
    for (size_t i = 1; i < measurements.size(); ++i){
        sum += measurements[i];
    }
    return (sum / measurements.size()).count();
}

int64_t Timer::last() const {
    return measurements[measurements.size() - 1].count();
}

void Timer::reset() {
    measurements.clear();
}









