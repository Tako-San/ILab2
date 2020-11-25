#include "vec.h"

namespace Geom
{
    double & Vec::get( unsigned idx )
    {
        return *(&x + idx % 3);
    }

    Vec::Vec( double x, double y, double z ) : x{x}, y{y}, z{z}
    {}

    Vec::Vec( double r ) : x{r}, y{r}, z{r}
    {}


    #define cmp( x ) std::abs(x - v.x) < ACCURACY
    bool Vec::operator ==( const Vec & v ) const
    {
        return cmp(x) && cmp(y) && cmp(z);
    }
    #undef cmp

    bool Vec::operator !=( const Vec & v ) const
    {
        return !(*this == v);
    }

    Vec & Vec::normalise( )
    {
        return (*this /= (*this).len());
    }

    Vec Vec::perp2D( ) const
    {
        return Vec{y, -x, 0};
    }

    void Vec::print( ) const
    {
        std::cout << "(" << x << ", " << y << ", " << z << ")^T";
    }

    Vec & Vec::operator +=( const Vec & v )
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    Vec & Vec::operator -=( const Vec & v )
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    Vec & Vec::operator *=( double num )
    {
        x *= num;
        y *= num;
        z *= num;

        return *this;
    }

    Vec & Vec::operator /=( double num )
    {
        x /= num;
        y /= num;
        z /= num;

        return *this;
    }

    Vec Vec::operator -( ) const
    {
        return Vec(-x, -y, -z);
    }

    double Vec::operator []( unsigned idx ) const
    {
        return *(&x + idx % 3);
    }

    double Vec::len( ) const
    {
        return sqrt(x * x + y * y + z * z);
    }

    /* dot product */
    double operator &( const Vec & v1, const Vec & v2 )
    {
        double res = v1[X] * v2[X] + v1[Y] * v2[Y] + v1[Z] * v2[Z];
        return res;
    }

    /* vector product */
    Vec operator %( const Vec & v1, const Vec & v2 )
    {
        return Vec(v1[Y] * v2[Z] - v1[Z] * v2[Y],
                   v1[Z] * v2[X] - v1[X] * v2[Z],
                   v1[X] * v2[Y] - v1[Y] * v2[X]);
    }

    std::istream & operator >>( std::istream & ist, Vec & v )
    {
        ist >> v.x >> v.y >> v.z;
        return ist;
    }

    Vec operator +( const Vec & v1, const Vec & v2 )
    {
        return Vec(v1) += v2;
    }

    Vec operator -( const Vec & v1, const Vec & v2 )
    {
        return Vec(v1) -= v2;
    }

    Vec operator *( const Vec & v, double n )
    {
        return Vec(v) *= n;
    }

    Vec operator *( double n, const Vec & v )
    {
        return Vec(v) *= n;
    }

    Vec normalise( const Vec & v )
    {
        return Vec(v).normalise();
    }

    std::ostream & operator <<( std::ostream & ost, const Vec & v )
    {
        ost << "(" << v[X] << ", " << v[Y] << ", " << v[Z] << ")^T";
        return ost;
    }
}
