#include <iostream>
#include <thread>
#include <chrono>

#include "cache/Cache.h"
#include "cache/LRUCache.h"

void printResult(const std::string& key, const std::string& value) {
    if (value.empty())
        std::cout << "GET " << key << " -> MISS\n";
    else
        std::cout << "GET " << key << " -> HIT (" << value << ")\n";
}

int main() {
    std::cout << "=== In-Memory Cache Demo (TTL + LRU) ===\n\n";

    // Create cache with capacity = 2 and LRU eviction
    Cache cache(
        2,
        std::make_unique<LRUCache>()
    );

    std::cout << "[STEP 1] Insert A and B (TTL = 3 seconds)\n";
    cache.put("A", "Apple", 3000);
    cache.put("B", "Banana", 3000);

    printResult("A", cache.get("A")); // HIT
    printResult("B", cache.get("B")); // HIT

    std::cout << "\n[STEP 2] Access A again (A becomes most recently used)\n";
    printResult("A", cache.get("A"));

    std::cout << "\n[STEP 3] Insert C (capacity exceeded -> LRU eviction)\n";
    cache.put("C", "Cherry", 3000);

    // B should be evicted (least recently used)
    printResult("B", cache.get("B")); // MISS
    printResult("C", cache.get("C")); // HIT

    std::cout << "\n[STEP 4] TTL expiration demo\n";
    cache.put("D", "Date", 1000);
    printResult("D", cache.get("D")); // HIT

    std::cout << "Sleeping for 1.5 seconds...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    printResult("D", cache.get("D")); // MISS (expired)

    std::cout << "\n=== Demo Completed ===\n";
    return 0;
}
