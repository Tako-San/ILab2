#include "vec.h"

bool Vec::operator == ( const Vec & v ) const
{
#define cmp( x ) std::abs(x - v.x) < ACCURACY

    return cmp(x) && cmp(y) && cmp(z);

#undef cmp
}

bool Vec::operator != ( const Vec & v ) const
{
    return !(*this == v);
}



Vec & Vec::normalise( )
{
    return (*this /= !(*this));
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

Vec Vec::operator - ( ) const
{
    return Vec(-x, -y, -z);
}



double Vec::operator [] ( unsigned idx ) const
{
    return *(&x + idx % 3);
}

double Vec::operator ! ( ) const
{
    return sqrt(x*x + y*y + z*z);
}



/* dot product */
double operator & ( const  Vec & v1, const Vec & v2 )
{
    return (v1[X] * v2[X] + v1[Y] * v2[Y] + v1[Z] * v2[Z]);
}

/* vector product */
Vec operator % ( const Vec & v1, const Vec & v2)
{
    return Vec(v1[Y] * v2[Z] - v1[Z] * v2[Y],
               v1[Z] * v2[X] - v1[X] * v2[Z],
               v1[X] * v2[Y] - v1[Y] * v2[X]);
}



std::ostream & operator << ( std::ostream & ost, const Vec & v )
{
    ost << "(" << v.x << ", " <<  v.y << ", " << v.z << ")^T";
    return ost;
}



Vec operator + ( const Vec & v1, const Vec & v2 )
{
    // return Vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    return Vec(v1) += v2;
}

Vec operator - ( const Vec & v1, const Vec & v2 )
{
    // return Vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    return Vec(v1) -= v2;
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
    return Vec(v) *= n;
}

Vec normalise( const Vec & v )
{
    return Vec(v).normalise();
}


