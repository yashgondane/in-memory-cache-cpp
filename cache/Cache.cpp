#include "Cache.h"
#include "../utils/Timer.h"

Cache::Cache(int capacity,
             std::unique_ptr<EvictionPolicy> policy)
    : capacity(capacity), policy(std::move(policy)) {}

std::string Cache::get(const std::string& key) {
    auto it = store.find(key);
    if (it == store.end()) {
        return ""; // MISS
    }

    // Check TTL
    if (Timer::isExpired(it->second.expiry)) {
        policy->remove(key);
        store.erase(it);
        return ""; // MISS due to expiry
    }

    // HIT
    policy->touch(key);
    return it->second.value;
}

void Cache::put(const std::string& key,
                const std::string& value,
                long long ttl_ms) {
    long long expiryTime = Timer::now() + ttl_ms;

    // If key already exists, overwrite
    if (store.find(key) != store.end()) {
        store[key] = {value, expiryTime};
        policy->touch(key);
        return;
    }

    // If capacity full, evict
    if ((int)store.size() >= capacity) {
        std::string evictedKey = policy->evict();
        if (!evictedKey.empty()) {
            store.erase(evictedKey);
        }
    }

    // Insert new entry
    store[key] = {value, expiryTime};
    policy->touch(key);
}
