//Question 8 TME3
#ifndef INVERT_H_
#define INVERT_H_

#include <unordered_map>
#include <forward_list>
#include <vector>
#include <functional>

template <typename K, typename V>
std::unordered_map<V, std::forward_list<K>> invert(const std:unordered_map<K, V> & src) {
    std::unordered_map<V, std::forward_list<K>> dest;
    for (auto & e : src) {
        dest[e.second].push_front(e.first);
    }
    return dest;
}

template <typename T>
std::unordered_map<std::string, std::forward_list<T>> groupBy(const std::vector<T> & src) {
    std::unordered_map<std::string, std::forward_list<T>> dest;
    for (auto & e : src) {
        dest[e.getPrenom()].push_front(e);
    }
    return dest;
}

#endif