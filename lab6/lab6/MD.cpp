#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <vector>
#include <math.h>

//multidictionar liste intrepatrunse
#define NIL -1
#define NULL_TCheie 0
using namespace std;
// BC theta(1), WC theta(capacity), OC O(capacitaty)
int MD::actPrimLiber()
{//actualizm prmLiber dupa ce a fost ocupat
	int poz = primLiber;
	if (table[poz].first == -100000) {
		return poz;
	}
	else {
		for (int i = 0; i < cap; i++) {
			if (table[i].first == -100000)//primul liber va avea -100000 valoarea
				return i;
		}
	}
}

//complexitate theta(1)
int MD::d(TCheie e) const
{
	//daca nu tranzmit -hash_poz pica la teste la nr negative din tablou
	int hash_poz= e % cap;
	if (hash_poz > 0) {
		return hash_poz;
	}
	else {
		return -hash_poz;
	}
}

//theta(capacity)
void MD::resize()
{
	TElem* new_table = new TElem[cap * 2];
	int* new_urm = new int[cap * 2];
	for (int i = 0; i < cap; i++) {
		new_table[i] = table[i];
		new_urm[i] = urm[i];
	}
	for (int i = cap; i < cap * 2; i++)
	{
		new_table[i].first = -100000;
		new_table[i].second = -100000;
		new_urm[i] = -1;
	}
	primLiber = cap;
	cap = cap * 2;
	delete[] table;
	delete[] urm;
	table = new_table;
	urm = new_urm;
}

//Complexitate theta(capacity)-best case, theta(capacity^2)-worst case, theta(capacity^2)-average.Overall O(m^2)
void MD::rehash()
{
	TElem* old_table = new TElem[cap];
	for (int i = 0; i < cap; i++) {
		old_table[i] = table[i];
	}
	int old_lenght = lenght;
	for (int i = 0; i < cap; i++) {
		table[i].first = -100000;
		table[i].second = -100000;
		urm[i] = -1;
	}
	primLiber = actPrimLiber();
	lenght = 0;
	for (int i = 0; i < old_lenght; i++) {
		adauga(old_table[i].first, old_table[i].second);
	}
}

//theta(capacity)
TCheie MD::cheieMaxima() const
{
	
	int max = 0;
	TCheie c;
	for (int i = 0; i < cap; i++)
	{
		vector<TValoare>values = cauta(table[i].first);
		if (values.size() == 0) return NULL_TCheie;
		if (values.size() > max) {
			max = values.size();
			c = table[i].first;
		}
	}
	return c;
}

//theta(capacity)
MD::MD() {
	/* de adaugat */
	cap = 20;
	primLiber = 0;
	lenght = 0;
	table = new TElem[cap];
	urm = new int[cap];
	for (int i = 0; i < cap; i++) {
		urm[i] = -1;
		table[i].first = -100000;
		table[i].second = -100000;
	}

}


void MD::adauga(TCheie c, TValoare v) {//O(capacity*capacity)
	/* de adaugat */
	int poz = d(c);
	if (lenght == cap) {
		resize();//theta(capacity)
		rehash();//2 for cu theta(capacity) si apoi apeleaza de add capacity ori
	}
	if (table[poz].first == -100000) {//locatia e libera, memoram
		table[poz].first = c;
		table[poz].second = v;
		urm[poz] = -1;
		lenght++;
	}
	else {
		table[primLiber].first = c;
		table[primLiber].second = v;
		urm[primLiber]= - 1;
		while (urm[poz] != -1) {
			poz = urm[poz];
		}
		urm[poz] = primLiber;
		lenght++;
	}
	if (table[primLiber].first != -100000) {
		primLiber = actPrimLiber();
	}
	
}


bool MD::sterge(TCheie c, TValoare v) {//O(capacity)
	/* de adaugat */
	int i = d(c);
	int j = -1;
	int index = 0;
	while (index < cap && j == -1)
	{
		if (urm[index] == i) {
			j = index;
		}
		else index++;
	}
	while (i != -1 && !(table[i].first == c && table[i].second == v)){
		j = i;
		i = urm[i];
	}
	if (i == -1) {
		return false;//(cheie, valoare) nu exista
	}
	else {
		bool gasit = false;
		int p;
		int pp;
		do {
			p = urm[i];
			pp = i;
			while (p != -1 && d(table[p].first) != i) {
				pp = p;
				p = urm[p];
			}
			if (p == -1) {
				gasit = true;
			}
			else {
				table[i] = table[p];
				j = pp;
				i = p;
			}
		} while (!gasit);
		if (j != -1) urm[j] = urm[i];
		table[i].first = -100000;
		table[i].second = -100000;
		urm[i] = -1;
		if (primLiber > i) primLiber = i;
		lenght = lenght - 1;
		return true;
	}
}

//Complexitate theta(1)-best case, theta(capacity)-worst case. Overall O(capacity) 
vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */
	vector<TValoare> values;
	int poz = d(c);
	while (poz != -1) {
		if (table[poz].first == c) {
			values.push_back(table[poz].second);
		}
		poz = urm[poz];
	}
	return values;
}

//theta(1)
int MD::dim() const {
	/* de adaugat */
	return lenght;
}

//theta(1)
bool MD::vid() const {
	/* de adaugat */
	if (lenght == 0) return true;
	else return false;
}

//theta(1)
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

//theta(1)
MD::~MD() {
	/* de adaugat */
	delete[] table;
	delete[] urm;
}

