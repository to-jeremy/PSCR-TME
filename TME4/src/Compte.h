#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;

	void lock() const { //Méthide lock() const pour TME3
		m.lock();
	}

	void unlock() const { //Méthide unlock() const pour TME3
		m.unlock();
	}

	bool try_lock() const { //Méthide try_lock() const pour TME3
		return m.try_lock();
	}
};

}
