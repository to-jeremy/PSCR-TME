//Question 1 et 2 TME3

#define UTILS_H_

#include <string>

namespace pr {

template<typename iterator>
site_t count(iterator begin, iterator end){ //Q1
    size_t sz = 0;
    while (begin != end) {
        ++begin;
        ++sz;
    }
    return sz;
}

template<typename iterator, typename T> //Q2
size_t count_if_equal (iterator begin, iterator end, const T& target) {
    size_t sz =0;
    while (begin != end) {
        if (*begin == target) {
            ++sz;
        }
        ++begin;
    }
    return sz;
}
}

#endif