#include "Banque.h"
#include <random>
#include <iostream>

using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTE = 2; // Nombre de comptes dans la banque
const int JP = 200; // Solde initial de chaque compte

void operation_transaction(pr::Banque& bank, int numTransactions) {
	for (int i = 0; i < numTransactions; ++i) {
        size_t debiteur = rand() % NB_COMPTE;
        size_t crediteur = rand() % NB_COMPTE;
        unsigned int montant = rand() % 100 + 1; // Un montant aléatoire entre 1 et 100

        bank.transfert(debiteur, crediteur, montant);

        // Simule un délai aléatoire entre 0 et 20 ms
        this_thread::sleep_for(chrono::milliseconds(rand() % 21));
    }
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
