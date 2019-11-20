#include <cmath>
#include "vector3.h"
#include "point3.h"

vector3::vector3() {
//modif RR, 05/12/2006, passage 0.0 -> 0.0f
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

//modif RR 02/12/2006, parametre const double -> const double&
vector3::vector3(const long double& X,const long double& Y,const long double& Z) {
    x=X;
    y=Y;
    z=Z;
}

/*!
* \author RR
* \date 05/12/2006
*/
vector3::vector3(const vector3& _v) {
 x=_v.x;
 y=_v.y;
 z=_v.z;
}

/*!
* \author RR
* \date 05/12/2006
*/
vector3::~vector3() {
    //rien
}

/*!
* \author RR
* \date 05/12/2006
*/
vector3::vector3(const point3& _P) {
    x=_P.x;
    y=_P.y;
    z=_P.z;
}


/*!
* \author RR
* \date 05/12/2006
*/
vector3::vector3(const point3& _A, const point3& _B) {
    x=_B.x-_A.x;
    y=_B.y-_A.y;
    z=_B.z-_A.z;
}

int vector3::operator==(const vector3 &op) const {
    return(x==op.x && y==op.y && z==op.z);
}

vector3& vector3::operator=(const vector3 &op) {
    x=op.x;
    y=op.y;
    z=op.z;
    return *this;
}

vector3& vector3::operator=(const point3 &op) {
x = op.x;	y = op.y; z = op.z;

return *this;
}

vector3 vector3::operator+() const {
    return(*this);
}

vector3 vector3::operator+(const vector3 &op) const {
    return(vector3(x+op.x,y+op.y,z+op.z));
}

/*! RR 02Juillet2008
*/
vector3 vector3::operator+(const point3 & _p) const {
    return(vector3(x + _p.x, y + _p.y, z + _p.z));
}


vector3&
vector3::operator+=(const vector3 &op) {
    x+=op.x;
    y+=op.y;
    z+=op.z;
    return *this;
}

vector3
vector3::operator-()const {
    return(vector3(-x,-y,-z));
}

vector3
vector3::operator-(const vector3 &op)const {
    return(vector3(x-op.x,y-op.y,z-op.z));
}

vector3&
vector3::operator-=(const vector3 &op) {
    x-=op.x;
    y-=op.y;
    z-=op.z;
    return *this;
}

vector3&
vector3::operator*=(const long double op) {
    x*=op;
    y*=op;
    z*=op;
    return *this;
}

vector3
vector3::operator*(const long double op)const {
    return(vector3(x*op,y*op,z*op));
}

vector3&
vector3::operator/=(const long double op) {
    x/=op;
    y/=op;
    z/=op;
    return *this;
}

vector3
vector3::operator/(const long double op)const {
    return(vector3(x/op,y/op,z/op));
}

double
vector3::operator*(const vector3 &op)const {
    return(x*op.x+y*op.y+z*op.z);
}

vector3&
vector3::operator^=(const vector3 &op) {
    vector3 temp(	y*op.z-z*op.y,
                  z*op.x-x*op.z,
                  x*op.y-y*op.x );
    x=temp.x;
    y=temp.y;
    z=temp.z;
    return *this;
}


vector3
vector3::operator^(const vector3 &op)const {
    return(vector3(	y*op.z-z*op.y,
                    z*op.x-x*op.z,
                    x*op.y-y*op.x ));
}


vector3
vector3::normalize(const long double lg) {
    double lgtemp;
    if (x!=0 || y!=0 || z!=0) {
        lgtemp=sqrt(x*x+y*y+z*z);
        lgtemp=lg/lgtemp;
        x*=lgtemp;
        y*=lgtemp;
        z*=lgtemp;
    }
    return(*this);
}

double
vector3::length() {
    return(sqrt(x*x+y*y+z*z));
}
