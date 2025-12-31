# In-Memory Cache System with TTL & LRU Eviction (C++)

A backend-style in-memory cache system implemented in C++ that models real-world
cache behavior including **time-based expiration (TTL)** and **capacity-based eviction
using the LRU policy**.

This project focuses on **system design thinking**, not just data structures.

---

## Features

- O(1) `get` and `put` operations
- Time-To-Live (TTL) support with automatic expiry
- Capacity limit enforcement
- LRU (Least Recently Used) eviction policy
- Policy-based design (eviction logic decoupled from cache core)
- Monotonic time handling using `std::chrono::steady_clock`

---

## System Behavior

### `get(key)`
- Returns value if key exists and is not expired
- Refreshes LRU position on hit
- Returns empty result on miss or expiry

### `put(key, value, ttl_ms)`
- Inserts or updates a key with a TTL
- Resets expiry and LRU position if key already exists
- Evicts least recently used key when capacity is full

### Expiry Handling
- Expired keys are removed lazily during `get` and `put`
- Expired entries do not count toward capacity

---

## 📁 Project Structure

cache-system/
│
├── cache/
│ ├── Cache.h
│ ├── Cache.cpp
│ ├── EvictionPolicy.h
│ ├── LRUCache.h
│ └── LRUCache.cpp
│
├── utils/
│ ├── Timer.h
│ └── Timer.cpp
│
├── main.cpp
└── README.md


---

## Core Design Choices

- **unordered_map** for O(1) key lookup
- **doubly linked list** for LRU ordering
- **policy interface** for extensible eviction strategies
- **time abstraction** isolated in a utility module
- **no global state**, clean ownership via `std::unique_ptr`

---

## Build & Run

From the project root directory:

```powershell
g++ main.cpp cache/Cache.cpp cache/LRUCache.cpp utils/Timer.cpp -o cache_demo
