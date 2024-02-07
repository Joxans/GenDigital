#include "LRUCache.h"

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache() : capacity(0) {}

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(size_t capacity) : capacity(capacity) {}


template <typename Key, typename Value>
void LRUCache<Key, Value>::pop() {
    auto last = list.back();
    map.erase(last.first);
    list.pop_back();
}


template <typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, const Value& value) {
    std::lock_guard<std::mutex> lock(mutex);

    auto item = map.find(key);

    if (item != map.end()) {     // if exist
        list.splice(list.begin(), list, item->second); // mark as last used
        item->second->second = value;
    } else {                        // put new
        if (map.size() >= capacity) // if oversize, remove last item
            pop();

        list.emplace_front(key, value);
        map[key] = list.begin();
    }
}

template <typename Key, typename Value>
std::optional<Value> LRUCache<Key, Value>::get(const Key& key) {
    std::lock_guard<std::mutex> lock(mutex);

    auto item = map.find(key);
    if (item != map.end()) {
        list.splice(list.begin(), list, item->second); // mark as last used
        return item->second->second;
    }
    // not found
    return std::nullopt;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::setCapacity(size_t newCapacity) {
    std::lock_guard<std::mutex> lock(mutex);
    capacity = newCapacity;

    // remove extra items
    while (map.size() > capacity)
        pop();
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    map.clear();
    list.clear();
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::getCapacity() const {
    std::lock_guard<std::mutex> lock(mutex);
    return capacity;
}

template <typename Key, typename Value>
size_t LRUCache<Key, Value>::getItemCount() const {
    std::lock_guard<std::mutex> lock(mutex);
    return map.size();
}

template class LRUCache<int, std::string>;