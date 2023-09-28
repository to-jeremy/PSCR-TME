#include <cstddef>
#include <iostream> //rajouter l'include iostream (librairie standard)
#include <string> //rajouter l'include string (librairie standard)
#include "List.h" //FAUTE : rajouter le fichier interface

namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

size_t Chainon::length() {
	size_t len = 1;
	if (next != nullptr) {
		len += next->length();
	}
	return len; //FAUTE : Renvoyer len au lieu de length()
}

void Chainon::print (std::ostream & os) const { //FAUTE : manque le const
	os << data ;
	if (next != nullptr) {
		os << ", ";
		next->print(os); //FAUTE : mettre à l'intérieur de la condition if
	}
}

// ******************  List
const std::string & List::operator[] (size_t index) const  {
	Chainon * it = tete;
	for (size_t i=0; i < index ; i++) {
		it = it->next;
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}

void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}

bool pr::List::empty() { //FAUTE : Ajout du préfixe de classe
	return tete == nullptr;
}

size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}

std::ostream & operator<< (std::ostream & os, const pr::List & vec) //FAUTE : il doit être inclus dans le namespace pr
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]";
	return os;
}

} // namespace pr

