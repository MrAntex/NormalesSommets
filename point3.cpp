#include <iostream>
#include "point3.h"
#include "vector3.h"

using namespace std;


/*!
*   \brief constructeur sans paramètres
*   \todo none
*   \note RR: modif 19/12/2006 : =0 -> =0.0 pour les doubles
*/
point3::point3() {
    x=0.0;
    y=0.0;
    z=0.0;
}

/*!
*   \brief constructeur à partir de 3 réels (double)
*   \todo none
*/
point3::point3(const long double X,const long double Y,const long double Z) {
    x=X;
    y=Y;
    z=Z;
}

/*!
*   \brief constructeur de copie
*   \todo none
*/
point3::point3(const point3& _p) {
    x=_p.x;
    y=_p.y;
    z=_p.z;
}


/*!
*   \brief constructeur de copie de vecteur3
*   \todo none
*/
point3::point3(const vector3& _v) {
    x=_v.x;
    y=_v.y;
    z=_v.z;
}

/*!
*   \brief destructeur
*   \todo none
*/
point3::~point3() {
    //rien
}

/*!
*   \brief conditionnelle ==
*   \todo none
*/
bool point3::operator==(const point3 &op)const {

    if (x==op.x && y==op.y && z==op.z)
        return true;
    else return false;
}

/*!
*   \brief affectation
*   \todo none
*/
point3& point3::operator=(const point3 &op) {
    x = op.x;
    y = op.y;
    z = op.z;

    return *this;
}

/*!
*   \brief affectation
*   \todo none
*/
point3& point3::operator=(const vector3 & _v) {
    x = _v.x;
    y = _v.y;
    z = _v.z;
    return *this;
}

/*!
*   \brief addition point+vecteur
*   \todo none
*/
point3 point3::operator+(const vector3 &op)const {
    return(point3(x+op.x,y+op.y,z+op.z));
}

/*!
*   \brief addition point+point
*   \todo none
*/
point3 point3::operator+(const point3 &op)const {
    return(point3(x+op.x,y+op.y,z+op.z));
}

/*!
*   \brief combinaison affectation/addition avec un vecteur (translation)
*   \todo none
*/
point3& point3::operator+=(const vector3 &op) {
    x+=op.x;
    y+=op.y;
    z+=op.z;
    return *this;
}

/*!
*   \brief soustraction de points
*   \todo none
*/
point3 point3::operator-(const point3 &op)const {
    return( point3 (x - op.x, y - op.y, z - op.z ) );
}

/*!
*   \brief combinaison affectation/multiplication par un scalaire
*   \todo none
*/
point3& point3::operator*=(const long double op) {
    x*=op;
    y*=op;
    z*=op;
    return *this;
}

/*!
*   \brief multiplication par un scalaire (mise à l'échelle)
*   \todo none
*/
point3 point3::operator*(const long double op)const {
    return(point3(x*op,y*op,z*op));
}

/*!
*   \brief combinaison affectation/division par un scalaire
*   \todo none
*   \note RR: modif 19/12/2006 : test sur op!=0
*/
point3& point3::operator/=(const long double op) {
        if (op!=0.0) {
            x/=op;
            y/=op;
            z/=op;
        }
return *this;
}

/*!
*   \brief division par un scalaire
*   \todo lever une exception si diviseur==0
*/
point3 point3::operator/(const long double op)const {
    return(point3(x/op,y/op,z/op));
}

/*!
*   \brief multiplication par un point (produit scalaire)
*   \todo none
*/
point3 point3::operator*(const point3 &op)const {
    return(point3(x*op.x,y*op.y,z*op.z));
}

/*!
*   \brief combinaison affectation/multiplication par un point
*   \todo none
*/
point3& point3::operator*=(const point3 &op) {
    x*=op.x;
    y*=op.y;
    z*=op.z;
    return *this;
}

/*!
*   \brief division par un point
*   \todo lever une exception si un des diviseurs==0
*/
point3 point3::operator/(const point3 &op)const {
    return(point3(x/op.x,y/op.y,z/op.z));
}

/*!
*   \brief combinaison affectation/division par un point
*   \todo lever une exception si un des diviseurs==0
*/
point3& point3::operator/=(const point3 &op) {
    x/=op.x;
    y/=op.y;
    z/=op.z;
    return *this;
}

/*!
*   \brief Permutation de 2 points
*   \todo à ne pas mettre dans la classe point C=C.permutation(A, B) ?
*/
void point3 :: Permutation(point3 *A, point3 *B) {
    point3 PEch;
    PEch = (*A);
    (*A) = (*B);
    (*B) = PEch;
}

/*!
*   \brief ecriture dans un flux ostream "(x, y, z)"
*   \todo none
*/
ostream& operator<<(ostream& _os, const point3 & _p) {
    _os << "[" << _p.x <<"," << _p.y << "," << _p.z  << "]";
    return(_os);
}

/*!
*   \brief lecture dans un flux istream "Entrez x:\n ...y:\n ...z:"
*   \todo none
*/
istream&  operator>>(istream& p, point3 &op) {
    cout << "Entrez x:";
    p >> op.x;
    cout << "Entrez y:";
    p >> op.y;
    cout << "Entrez z:";
    p >> op.z;

    return (p);
}
