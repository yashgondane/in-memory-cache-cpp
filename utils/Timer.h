#pragma once
#include <chrono>

class Timer {
public:
    // Returns current time in milliseconds
    static long long now();

    // Returns true if current time >= expiryTime
    static bool isExpired(long long expiryTime);
};
