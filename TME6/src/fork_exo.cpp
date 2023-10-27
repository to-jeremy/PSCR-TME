#include <iostream>
#include <vector> //Ajouter vector pour utiliser la fonction vector
#include <sys/wait.h> //AJouter pour utiliser le wait
#include <unistd.h>

void attaque(pid_t adversaire) {

}

void defense() {

}

void combat(pid_t adversaire) {

}

int main (int argc, const char ** argv) {
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

		/*if (pidf != 0) { //pere
			std::cout << "Processus" << getpid() << "rang i= " << i << " père = " << getppid();
			break;
		}
		wait(NULL);*/
	}

	//for (int k=1; k<=i && j==N ; k++) {
	for (i=0; i<N; i++){
		int status;
		pid_t fini = waitpid(children[i], &status, 0);

		std::cout << "Fin du fils " << fini << " detecté " << std::endl;
		std::cout << "Il est de rang " << WEXITSTATUS(status) << std::endl;
			
	}

	return 0;
}
