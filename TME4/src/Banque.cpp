#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	//unique_lock<mutex> g(m);

	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	if (deb < cred) {
		debiteur.lock(); //Question 4 TME4
		crediteur.lock(); //Question 4 TME4
	} else {
		crediteur.lock();
		debiteur.lock();
	}

	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}

	debiteur.unlock(); //Question 4 TME4
	crediteur.unlock(); //Question 4 TME4
}

size_t Banque::size() const {
	return comptes.size();
}

bool Banque::comptabiliser () const {
	//unique_lock<mutex> g(m);

	int attendu = initial * comptes.size();
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		compte.lock();

		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}

		bilan += compte.getSolde();
		id++;
	}

	for (const auto & compte : comptes) {
		compte.unlock();
	}

	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}

	return bilan == attendu;
}
}
