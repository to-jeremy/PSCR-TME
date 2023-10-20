#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <mutex>

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	mutable std::recursive_mutex m;

	// fonctions private, sans protection mutex
	bool empty() const {
		unique_lock<recursive_mutex> l(m);
		return sz == 0;
	}
	bool full() const {
		unique_lock<recursive_mutex> l(m);
		return sz == allocsize;
	}
public:
	std::condition_variable -any cv_pop;
	std::condition_variable -any cv_push;

	void setBlocking(bool b) {
		unique_lock<recursive_mutex> l(m);
		isBlocking = b;
		cv_pop.notify_one();
	}

	Queue(size_t size) :allocsize(size), begin(0), sz(0) {
		tab = new T*[size];
		memset(tab, 0, size * sizeof(T*));
	}
	size_t size() const {
		std::unique_lock<std::recursive_mutex> lg(m);
		return sz;
	}
	T* pop() {
		std::unique_lock<std::recursive_mutex> lg(m);
		while (empty()) {
			cv_pop.wait(l);
		}
		//auto ret = tab[begin];
		//tab[begin] = nullptr;
		T * ret = tab[begin];
		sz--;
		begin = (begin + 1) % allocsize;
		cv_push.notify_one();
		return ret;
	}
	bool push(T* elt) {
		std::unique_lock<std::recursive_mutex> lg(m);
		if (full()) {
			unique_lock<recursive_mutex> l(m);
			cv_push.wait(l);
		}
		tab[(begin + sz) % allocsize] = elt;
		sz++;
		cv_pop.notify_one();
		return true;
	}
	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			delete tab[ind];
		}
		delete[] tab;
	}
};

}

#endif /* SRC_QUEUE_H_ */
