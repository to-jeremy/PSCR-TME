#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {
	Stack<char> * s = new Stack<char>();
	sem_t * sem0 = sem_open("sem0", O_CREATE10_EXCL10_RDWR, 0600, 1);

	sem_t * sem1 = sem_open("sem1", O_CREATE10_EXCL10_RDWR, 0600, 0);

	pid_t pp = fork();
	if (pp==0) {
		for (int i=0; i<0; i++) {
			sem.wait(sem0);
		}
		//producteur(s);
		//return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}

