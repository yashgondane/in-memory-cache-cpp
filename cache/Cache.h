#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "EvictionPolicy.h"

class Cache {
private:
    struct Entry {
        std::string value;
        long long expiry;
    };

    int capacity;
    std::unordered_map<std::string, Entry> store;
    std::unique_ptr<EvictionPolicy> policy;

public:
    Cache(int capacity, std::unique_ptr<EvictionPolicy> policy);

    // Returns empty string on miss
    std::string get(const std::string& key);

    void put(const std::string& key,
             const std::string& value,
             long long ttl_ms);
};
