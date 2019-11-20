#include "iFaceTri.h"


iFaceTri&  iFaceTri::operator=(const iFaceTri & _op) {
	s0 = _op.s0;
	s1 = _op.s1;
	s2 = _op.s2;

	return (*this);
}

iFaceTri::iFaceTri(const iFaceTri & _f) {
	s0 = _f.s0;
	s1 = _f.s1;
	s2 = _f.s2;
}

iFaceTri::iFaceTri(const unsigned int _s0, const unsigned int _s1, const unsigned int _s2) {
	s0 = _s0;
	s1 = _s1;
	s2 = _s2;
}

