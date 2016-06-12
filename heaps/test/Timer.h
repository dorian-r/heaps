#ifndef HEAPS_TIMER_H
#define HEAPS_TIMER_H

#include <chrono>
#include <vector>

class Timer {
public:
    void start();
    void stop();
    int64_t average() const;
    int64_t last() const;
    void reset();
private:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start_time;
    std::vector<Clock::duration> measurements;
};


#endif //HEAPS_TIMER_H
