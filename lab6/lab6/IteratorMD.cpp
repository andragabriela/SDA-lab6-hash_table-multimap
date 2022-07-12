#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md) {//theta(capacity)
	/* de adaugat */
	curent = 0;
	deplasare();
}

TElem IteratorMD::element() const {
	/* de adaugat */
	if (valid())
		return md.table[curent];
	else throw;
}

bool IteratorMD::valid() const {
	/* de adaugat */
	return curent < md.cap;
}

void IteratorMD::urmator() {
	/* de adaugat */
	if (valid()) {
		curent++;
		deplasare();
	}
	else throw;
}

void IteratorMD::deplasare()
{
	while (curent < md.cap && md.table[curent].first == -100000) {
		curent++;
	}
}

void IteratorMD::prim() {
	/* de adaugat */
	curent = 0;
	deplasare();
}

