#include "vec.h"

bool Vec::operator == ( const Vec & v ) const
{
#define cmp( x ) std::abs(x - v.x) < ACCURACY

    return cmp(x) && cmp(y) && cmp(z);

#undef cmp
}

Vec & Vec::normalise( )
{
    *this /= !(*this);
    return *this;
}

Vec & Vec::operator += ( const Vec & v )
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vec & Vec::operator -= ( const Vec & v )
{

    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vec & Vec::operator *= ( double num )
{
    x *= num;
    y *= num;
    z *= num;

    return *this;
}

Vec & Vec::operator /= ( double num )
{
    x /= num;
    y /= num;
    z /= num;

    return *this;
}

Vec & Vec::operator = ( const Vec & v )
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

Vec Vec::operator - ( )
{
    return Vec(-x, -y, -z);
}

double Vec::operator ! ( ) const
{
    return sqrt(x*x + y*y + z*z);
}

double operator & ( const  Vec & v1, const Vec & v2 )
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vec operator % ( const Vec & v1, const Vec & v2)
{
    return Vec(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

Vec operator + ( const Vec & v1, const Vec & v2 )
{
    return Vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec operator - ( const Vec & v1, const Vec & v2 )
{
    return Vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec operator * ( const Vec & v, double n )
{
    /*Vec newborn(v);
    newborn *= n;
    return newborn;*/
    return Vec(v) *= n;
}

Vec operator * ( double n, const Vec & v )
{
    /*Vec newborn(v);
    newborn *= n;
    return newborn;*/
    return Vec(v) *= n;
}

Vec normalise( const  Vec & v )
{
    return Vec(v).normalise();
}

std::ostream & operator << ( std::ostream & ost, const Vec & unit )
{
    ost << "(" << unit.x << ", " <<  unit.y << ", " << unit.z << ")";
    return ost;
}

