template <typename K, typename V>

class HashMap{
public:
    struct HashMap{
        class Entry{
            const K key;
            V value;
        };
    }

    HashMap (site_t alloc) : buckets(alloc){};

    for (auto &&= buckets){
        for (auto &e= ){
            tmp_put(e_key, e_value);
        }
        this.buckets=tmp_buckets;
    }
    
    bool put (const k & key const k & value){
        size_t h=std::hash<k>()(key);
        site_t target=h%buckets.size();
        for(auto & ent: buckets [target]){
            if(ent.key == key){
                ent.value = value;
                return true;
            }
        }
        buckets[target]_push_front(Entry(key,value));
        emplace_front(key,value);
        return false;
    }
    
    template<typename K>
    struct hash{
        site_t operator (const K &) {};
    }

    iterator begin(){
    size_t index=0;
    for(   ; index<buckets.size(); ++index){
        if(!buckets[index].empty()){
            break;
        } //index==buckets.size()   size==0;<=>rendre end();
        
        return iterator(buckets,index,buckets[index]begin());
    }
    }
}