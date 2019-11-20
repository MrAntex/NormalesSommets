#ifndef _POINT3_H
#define _POINT3_H

#include <iostream>

class vector3;

/******************* point3 ******************/

class point3{
public:
	long double x;
	long double y;
	long double z;

	point3();  // (0,0,0) par defaut
	point3(const long double X,const long double Y,const long double Z);
    point3(const point3&);
	point3( const vector3 & );
    ~point3();

    bool        operator==(const point3 &)const;
	point3&     operator=(const point3 &);
	point3&     operator=(const vector3 &);

	point3      operator+(const vector3 &)const; //equivalent a une translation
	point3      operator+(const point3 &)const;
	point3&     operator+=(const vector3 &); //pareil
	point3		operator-(const point3 &)const; //definition d'un vecteur
	point3&     operator*=(const long double); //produit par un scalaire (a peu pres une homothetie)
	point3      operator*(const long double)const; //idem
	point3&     operator/=(const long double); //division par un scalaire (a peu pres une homothetie)
	point3      operator/(const long double)const; //idem
	point3      operator*(const point3 &)const;
	point3&     operator*=(const point3 &); //pareil :)
	point3      operator/(const point3 &)const; //pareil :)
	point3&     operator/=(const point3 &); //pareil :)

	void Permutation(point3 *, point3 *); // Permutation de deux points
	friend std::ostream&  operator<<(std::ostream&, const point3&);
	friend std::istream&  operator>>(std::istream&, point3 &);
};

#endif