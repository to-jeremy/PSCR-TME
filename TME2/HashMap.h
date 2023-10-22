//TME2 HashMap

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include <cstddef>
#include <ostream>

#include <forward_list>
#include <vector>

namespace pr {
    template <typename K, typename V>

    class HashMap {
    public:
        class Entry {
        public:
            const K key;
            V value;
            Entry(const K &k, const V &v) : key(k), value(v) {}
        };

    private:
        typedef std::vector<std::forward_list<Entry>> buckets_t;

        buckets_t buckets;

        size_t sz;

    public:
        HashMap(size_t size) : buckets(size), sz(0) {}

        V* get (const K & key) {
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            for (Entry & ent : buckets[target]) {
                if (ent.key==key){
                    return & ent.value;
                }
            }
            return nullptr;
        }

        bool put(const K &key, const V &value) {
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            for (auto &ent : buckets[target]) {
                if (ent.key == key) {
                    ent.value = value;
                    return true;
                }
            }
            sz++;
            buckets[target].emplace_front(key, value);
            return false;
        }

        size_t size() const { return sz ; }

        void grow() {
            HashMap other = HashMap(buckets.size()*2);
            for (auto & list : buckets) {
                for (auto & entry : list) {
                    other.put(entry.key, entry.value);
                }
            }
            buckets = other.buckets;
        }

        std::vector<Entry> getEntries() const {
            std::vector<Entry> entries;
            for (const auto& bucket : buckets) {
                for (const auto& entry : bucket) {
                    entries.push_back(entry);
                }
            }
            return entries;
        }


        //Q4 TME3 début
        class iterator {
            typename buckets_t::iterator buckend;

            typename buckets_t::iterator vit;

            typename std::forward_list<Entry>::iterator lit;

        public :
            iterator(const typename buckets_t::iterator & buckend, const typename buckets_t::iterator & vit, const typename std::forward_list<Entry>::iterator & lit):buckend(buckend), vit(vit), lit(lit){}

            iterator & operator++(){
                ++lit;

                if (lit == vit->end()) {
                    ++vit;

                    while (vit->empty() && vit != buckend) {
                        ++vit;
                    }

                    if (vit != buckend) {
                        lit = vit->begin();
                    }
                }
                return *this;
            }

            Entry & operator*(){
                return *lit;
            }

            bool operator!=(iterator other) {
                return vit != other.vit || lit != other.lit;
            }
        };

        iterator begin() {
            typename buckets_t::iterator vit = buckets.begin();

            while (vit->empty() && vit != buckets.end()) {
                ++vit;
            }

            if (vit != buckets.end()) {
                return iterator(buckets.end(), vit, vit->begin());
            } else {
                return end;
            }
        }

        iterator end() {
            return iteraor(buckets.end(), buckets.end(), buckets.front().end());
        }

        //Q4 TME3 fin
    };
}

#endif