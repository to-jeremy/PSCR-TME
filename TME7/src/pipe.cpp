#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h> //Partie Sémaphores
#include <sys/stat.h> //Partie Sémaphores
#include <semaphore.h> //Partie Sémaphores

using namespace std;


//Partie 1 : Fork, exec, pipe
//Question 1

void exec (int argc, chat ** args) {
    cout << "Args :";
    for (int i=0; i < argc; i++) {
        if (args[i] != nullptr) {
            cout << args[i] << " ";
        } else {
            break;
        }
    }
    cout << endl;

    if (execv(agrs[0], args) == -1) {
        perror("exec");
        exit(3);
    }
}

int main (int argc, char ** argv) {

    char * args1[argc];
    char * args2[argc];

    memset(args1, 0, argc * sizeof(char *));
    memset(args2, 0, argc * sizeof(char *));

    int arg = 1;

    for ( ; arg < argc; arg++) {
        if (!strcmp(argv[arg], "|")) {
            arg++;
            break;
        } else {
            args[arg -1] = argv[arg];
        }
    }

    for (int i=0; arg < argc; i++; arg++) {
        args2[i] = argv[arg];
    }

    int tube_principal[2];
    pid_t p_fils;

    if (pipe(tube_principal) == -1) {
        perror("pipe");
        exit(1);
    }

    if ((p_fils = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (p_fils == 0) { /*fils 1*/
        dup2(tube_principal[1], STDOUT_FILENO);
        close(tube_principal[1]);
        close(tube_principal[0]);

        exec(argc, args1);
    }

    if ((p_fils = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (p_fils == 0) { /*fils 2*/
        dup2(tube_principal[0], STDOUT_FILENO);
        close(tube_principal[0]);
        close(tube_principal[1]);

        exec(argc, args2);
    }

    close(tube_principal[0]);
    close(tube_principal(1));

    wait(0);
    wait(0);

    return 0;

}

/*int main() {

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

}*/

//Fin question 1

//dup2(pipe1 pfd[1], 1);
//dup2(pipe0 pfd[0], 0);

/*Détails persos à connaitre*/

/*descripteur
entrée : 0
sortie : 1
sortie erreur : 2

wc -w : renvoie le nombre de mots dans un fichier
wc -l : renvoie le nombre de lignes
wc -c : le nombre de caractères*/

