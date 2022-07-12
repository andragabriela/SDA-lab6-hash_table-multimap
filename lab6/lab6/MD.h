#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	int cap; //numarul de locatii din tabela de dispersie=m din pseudocod
	TElem* table ; //vectorul elementelor - vector static
	int* urm;
	int primLiber;
	int lenght; //size

	int actPrimLiber();
	// functia de dispersie extinsa 
	int d(TCheie e) const;
	void resize();
	void rehash();
	
public:
	// constructorul implicit al MultiDictionarului
	MD();
	TCheie cheieMaxima() const;
	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

