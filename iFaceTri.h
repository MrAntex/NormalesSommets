#ifndef _H_IFACETRI
#define _H_IFACETRI

class iFaceTri {

public:
	unsigned int s0, s1, s2;
	iFaceTri() {};
	~iFaceTri() {};
	iFaceTri& operator=(const iFaceTri&);
	iFaceTri(const iFaceTri&);
	iFaceTri(const unsigned int _s0, const unsigned int _s1, const unsigned int _s2);

};

#endif