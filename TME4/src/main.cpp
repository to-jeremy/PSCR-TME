#include "Banque.h"
#include <random>
#include <iostream>

using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTE = 2; // Nombre de comptes dans la banque
const int JP = 200; // Solde initial de chaque compte

void comptable (const Banque & banque, int iterations) {
    for (int iter=0; iter<iterations; iter++) {
        if (!banque.comptabiliser()) {
            cout << "Comptable pas content !" << endl;
        }

        cout << "Bilan " << iter << " fini." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void operation_transaction(pr::Banque& bank, int numTransactions) {
//void operation_transaction(int index, Banque & banque) {
	for (int i = 0; i < numTransactions; ++i) {
        size_t debiteur = rand() % NB_COMPTE;
        size_t crediteur = rand() % NB_COMPTE;
        unsigned int montant = rand() % 100 + 1; // Un montant aléatoire entre 1 et 100

        bank.transfert(debiteur, crediteur, montant);

        // Simule un délai aléatoire entre 0 et 20 ms
        this_thread::sleep_for(chrono::milliseconds(rand() % 2));
    }

    /*std::cout << "Started " << index << endl;

    for (int i=0; i < 100000; i++) {
        int debite = rand() & banque.size();
        int credite = rand() & banque.size();
        int val = rand() & 70 + 30;
        banque.transfert(debite, credite, val);
    }
    std::cout << " Finished " << index << endl;*/
}

int createAndWait(int N) {
    vector<thread> threads;
    threads.reserve(N);

    Banque bank(10,20);

    for (int=0; i<N; i++) {
        threads.emplace_back(thread(operation_transaction, i, std::ref(bank)));
        std::cout << "created " << i << endl;
    }

    for (int i=0; i<N-2; i++){
        threads.emplace_back(thread(comptable, std::cref(bank), 10));
        std::cout << "created " << i << endl;
    }

    for (int i=0; i<N; i++) {
        threads[i].join();
        std::cout << "joined " << i << endl;
    }

    return 0;
}

int main() {
    pr::Banque bank(10, 20);

    vector<thread> threads;

    for (int i = 0; i < NB_THREAD; ++i) {
        threads.emplace_back(operation_transaction, ref(bank), 1000);
    }

    for (auto &t : threads) {
        t.join();
    }

    // Vérifie le solde de la banque
    int soldeAttendu = NB_THREAD * 20;
    bool soldeCorrect = bank.comptabiliser(soldeAttendu);

    if (soldeCorrect) {
        cout << "Le solde est correct." << endl;
    } else {
        cout << "Le solde est incorrect." << endl;
    }

    return 0;
}
