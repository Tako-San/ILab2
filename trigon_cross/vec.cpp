#include "vec.h"

bool Vec::operator == ( const Vec & v ) const
{
#define cmp( x ) std::abs(x - v.x) < ACCURACY

    return cmp(x) && cmp(y) && cmp(z);

#undef cmp
}

Vec Vec::operator + ( const Vec & v ) const
{
    return Vec(x + v.x, y + v.y, z + v.z);
}

Vec Vec::operator - ( const Vec & v ) const
{
    return Vec(x - v.x, y - v.y, z - v.z);
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

Vec & Vec::operator - ( )
{
    x = -x;
    y = -y;
    z = -z;

    return *this;
}

Vec & Vec::operator = ( const Vec & v )
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}


std::ostream & operator << ( std::ostream & ost, const Vec & unit )
{
    ost << "(" << unit.x << ", " <<  unit.y << ", " << unit.z << ")";
    return ost;
}

double Vec::operator ! ( ) const
{
    return sqrt(x*x + y*y + z*z);
}

Vec Vec::operator % ( const Vec &v ) const
{
    return Vec(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


