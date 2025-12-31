#include "LRUCache.h"

void LRUCache::touch(const std::string& key) {
    // If key already exists, remove old position
    if (pos.find(key) != pos.end()) {
        order.erase(pos[key]);
    }

    // Insert key at front (most recent)
    order.push_front(key);
    pos[key] = order.begin();
}

void LRUCache::remove(const std::string& key) {
    if (pos.find(key) == pos.end()) return;

    order.erase(pos[key]);
    pos.erase(key);
}

std::string LRUCache::evict() {
    if (order.empty()) return "";

    // Least recently used = back
    std::string key = order.back();
    order.pop_back();
    pos.erase(key);

    return key;
}
