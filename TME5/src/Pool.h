#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) ;

	void poolWorker(Queue<Job> queue) {
		while(true) {
			Job *j = queue.pop();
			if(j==nullptr) {
				break;
			}
			J -> run();
			delete j;
		}
	};

	void start (int nbthread) {
		threads_reserve (nbthread);
		for (int i=0; i<nbthread; ++i) {
			threads.emplace_back(poolWorker, ref(queue));
		}
	};

	void submit (Job * job) {
		queue.push(j);
	};

	void stop() {
		queue.setBlocking(false);
		for (auto &t.threads) {
			t.join();
		}
		threads.clear();
	};

	~Pool() ;
};

}
