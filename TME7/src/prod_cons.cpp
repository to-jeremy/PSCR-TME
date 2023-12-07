#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> //Partie 2
#include <sys/mman.h> //Partie 2
#include "Stack_cor.h" //Partie 2
#include <fcntl.h> //Partie 2
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

//Partie 2
//Ajout d'un vecteur
vector<pid_t> tokill;

//Fonction kill
void fct_kill(int) {
	for (auto p : tokill) {
		kill(p, SIGINT);
	}
}

int main () {
	//Question 2
	size_t shmsize = sizeof(Stack<char>);
	cout << "Taille du segment d'allocation : " << shmsize << endl;

	int fd;
	void * addr;

	bool anonyme = false;

	if (anonyme) {
		addr = mmap(nullptr, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

		if (aadr == MAP_FAILED) {
			perror("Anonyme mmap");
			exit(1);
		}
	} else {
		fd = shm_open("/myshm", O_CREAT | O_EXCL | O_RDWR 0666);

		if (fd < 0) {
			perror("shm_open");
			return 1;
		}

		if (ftruncate(fd, shmsize) != 0) {
			perror("ftruncate");
			return 1;
		}

		addr = mmap(nullptr, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		if (addr = MAP_FAILED) {
			perror("Anonyme mmap");
			exit(1);
		}
	}

	Stack<char> * s = new Stack<char>();
	//sem_t * sem0 = sem_open("sem0", O_CREATE10_EXCL10_RDWR, 0600, 1);

	//sem_t * sem1 = sem_open("sem1", O_CREATE10_EXCL10_RDWR, 0600, 0);

	pid_t pp = fork();
	if (pp==0) {
		for (int i=0; i<0; i++) {
			producteur(s);
			return 0;
		}
		//producteur(s);
		//return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	} else {
		tokill.push_back(pc);
	}

	signal(SIGINT, fct_kill);

	wait(0);
	wait(0);

	s ->~Stack();

	if (munmap(addr, shmsize) != 0) {
		perror("munmap");
		exit(1);
	}

	if (!anonyme) {
		if (shm_unlink("myshm") != 0) {
			perror("Unlink sem");
		}
	}

	//delete s;
	//return 0;
}

