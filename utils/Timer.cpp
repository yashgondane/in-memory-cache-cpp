#include "Timer.h"

long long Timer::now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch()
           ).count();
}

bool Timer::isExpired(long long expiryTime) {
    return now() >= expiryTime;
}
