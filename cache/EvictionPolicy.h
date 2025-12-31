#pragma once
#include <string>

// Abstract eviction policy interface
class EvictionPolicy {
public:
    virtual ~EvictionPolicy() {}

    // Called when a key is accessed (get or put)
    virtual void touch(const std::string& key) = 0;

    // Called when a key is removed from cache
    virtual void remove(const std::string& key) = 0;

    // Returns key to evict
    virtual std::string evict() = 0;
};
