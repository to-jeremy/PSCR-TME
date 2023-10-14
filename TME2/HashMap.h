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


        /*template <typename K>
        struct hash
        {
            site_t operator(const K &){};
        }

        iterator begin() {
            size_t index = 0;
            for (; index < buckets.size(); ++index)
            {
                if (!buckets[index].empty())
                {
                    break;
                } // index==buckets.size()   size==0;<=>rendre end();

                return iterator(buckets, index, buckets[index] begin());
            }
        }*/
    };
}

#endif