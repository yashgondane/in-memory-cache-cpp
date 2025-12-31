#pragma once
#include "EvictionPolicy.h"
#include <unordered_map>
#include <list>
#include <string>

// LRU eviction policy implementation
class LRUCache : public EvictionPolicy {
private:
    // Most recent at front, least recent at back
    std::list<std::string> order;

    // key -> iterator in list
    std::unordered_map<std::string, std::list<std::string>::iterator> pos;

public:
    void touch(const std::string& key) override;
    void remove(const std::string& key) override;
    std::string evict() override;
};
