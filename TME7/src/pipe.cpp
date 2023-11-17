#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;


//Partie 1 : Fork, exec, pipe
//Question 1
int main() {

    pid_t p, f1, f2;
    p=getpid();
    int pfd[2];

    if(pipe(pfd)) {
        perror("Pipe");
        exit(1);
    }

    if(!(f1=fork())) { ///F1
        f1=getpid();
        close(pfd[1]);
        read(pfd[0], &f2, sizeof(pid_t));
        //printf(p, f1, f2);
        cout << "Pere : " << p << ", F1 = " << f1 << ", F2 = " << f2 << endl;
        return 0;
    }

    close(pfd[0]);

    if(!(f2=fork())) { //F2
        f2=getpid();
        close(pfd[1]);
        //printf(p, f1, f2);
        cout << "Pere : " << p << ", F1 = " << f1 << ", F2 = " << f2 << endl;
        return 0;
    }

    if(write(pfd[1], &f2, sizeof(pid_t)) != sizeof(pid_t)) {
        perror("Write");
    }

    close(pfd[1]);
    //printf(p, f1, f2);
    cout << "Pere : " << p << ", F1 = " << f1 << ", F2 = " << f2 << endl;
    wait(NULL);
    wait(NULL);
    return 0;

    int pos=-1;

}
//Fin question 1

dup2(pipe1, 1);
dup2(pipe0, 0);

/*Détails persos à connaitre*/

//descripteur
//entrée : 0
//sortie : 1
//sortie erreur : 2

//wc -w : renvoie le nombre de mots dans un fichier
//wc -l : renvoie le nombre de lignes
//wc -c : le nombre de caractères