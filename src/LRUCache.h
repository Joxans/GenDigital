#pragma once

#include <unordered_map>
#include <list>
#include <mutex>
#include <optional>

template <typename Key, typename Value>
class LRUCache {
    size_t capacity;
    mutable std::mutex mutex;

    std::list<std::pair<Key, Value>> list;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> map;

    void pop();

public:
    LRUCache();
    LRUCache(size_t capacity);
    ~LRUCache() = default;

    void setCapacity(size_t newCapacity);
    size_t getCapacity() const;
    size_t getItemCount() const;

    void put(const Key& key, const Value& value);
    std::optional<Value> get(const Key& key);

    void clear();
};