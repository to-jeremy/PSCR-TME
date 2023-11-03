#pragma once

#include "Compte.h"
#include <vector>

namespace pr {

class Banque {
	//mutable std::mutex m;
	//typedef std::vector<Compte> comptes_t;
	typedef std::vector<Compte> Comptes;
	//comptes_t comptes;
	Comptes comptes;
	const int initial;
public :
	Banque (size_t ncomptes, size_t solde) : comptes (ncomptes, Compte(solde)), initial(solde){
	}
	void transfert(size_t deb, size_t cred, unsigned int val) ;
	size_t size() const ;
	bool comptabiliser () const ;
};

}
