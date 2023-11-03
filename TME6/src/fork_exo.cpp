#include <iostream>
#include <vector> //Ajouter vector pour utiliser la fonction vector
#include <sys/wait.h> //AJouter pour utiliser le wait
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "rsleep.h"

//Question 3 pour le combat entre le processus principal (vador) et son fils (luke)
int PV = 5;

void handler (int sig) {
	if (sig == SIGUSR1) {
		PV--;
		std::cout << "Attaque reçue par " << getpid() << "; PV restants " << PV << std::endl;
		if (PV == 0) {
			std::cout << "Plus de vie pour " << getpid() << "; mort du processus." << std::endl;
			exit(1);
		}
	}
}

void attaque(pid_t adversaire) {
	signal(SIGUSR1, handler);
	if (kill(adversaire, SIGUSR1) < 0) {
		std::cout << "Detection de mort de l'adversaire de pid= " << adversaire << std::endl;
		exit(0);
	}
	randsleep();
}

void defense() {
	signal(SIGUSR1, SIG_IGN);

	randsleep();
}

void combat(pid_t adversaire) {
	while (1) {
		defense();
		attaque(adversaire);
	}
}

int main() {
	pid_t pere = getpid();
	pid_t pid = fork();
	srand(pid);

	if (pid == 0) {
		combat(pere);
	} else {
		combat(pid);
	}
	return 0;
}

//Fin question 3

/*int main (int argc, const char ** argv) {
	const int N = 3;
	std::vector<pid_t> children;

	int i;
	//int N = atoi(argv[i]);
	std::cout << "main pid=" << getpid() << std::endl;

	//for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
	for (i=0; i<N; i++){
		//std::cout << " i:j " << i << ":" << j << std::endl;
		pid_t pidf = fork();

		if (pidf == -1) {
			perror("fork");
			exit(1);
		}
		if (pidf == 0) { //fils
			//j=0;
			//std::cout << " k:j " << k << ":" << j << std::endl;
			std::cout << "Je suis le fils " << i << " de pid " << getpid() << " de parent " << getppid() << std::endl;
			return i;
		} else { //pere
			children.push_back(pidf);
		}

		//if (pidf != 0) { //pere
		//	std::cout << "Processus" << getpid() << "rang i= " << i << " père = " << getppid();
		//	break;
		//}
		//wait(NULL);
	}

	//for (int k=1; k<=i && j==N ; k++) {
	for (i=0; i<N; i++){
		int status;
		pid_t fini = waitpid(children[i], &status, 0);

		std::cout << "Fin du fils " << fini << " detecté " << std::endl;
		std::cout << "Il est de rang " << WEXITSTATUS(status) << std::endl;
			
	}

	return 0;
}*/
