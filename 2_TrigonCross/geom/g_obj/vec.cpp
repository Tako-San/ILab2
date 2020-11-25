#include "vec.h"

namespace Geom
{
    extern const Vec ZERO_VEC{0};

    double & Vec::get( unsigned idx )
    {
        return *(&x_ + idx % 3);
    }

    Vec::Vec( double x, double y, double z ) : x_{x}, y_{y}, z_{z}
    {}

    Vec::Vec( double r ) : x_{r}, y_{r}, z_{r}
    {}


    #define cmp( x ) std::abs(x - v.x) < ACCURACY
    bool Vec::operator ==( const Vec & v ) const
    {
        return cmp(x_) && cmp(y_) && cmp(z_);
    }
    #undef cmp

    bool Vec::operator !=( const Vec & v ) const
    {
        return !(*this == v);
    }

    Vec & Vec::normalise( )
    {
        return (*this /= len());
    }

    Vec Vec::perp2D( ) const
    {
        return Vec{y_, -x_, 0};
    }

    void Vec::print( ) const
    {
        std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")^T";
    }

    Vec & Vec::operator +=( const Vec & v )
    {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;

        return *this;
    }

    Vec & Vec::operator -=( const Vec & v )
    {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;

        return *this;
    }

    Vec & Vec::operator *=( double num )
    {
        x_ *= num;
        y_ *= num;
        z_ *= num;

        return *this;
    }

    Vec & Vec::operator /=( double num )
    {
        x_ /= num;
        y_ /= num;
        z_ /= num;

        return *this;
    }

    Vec Vec::operator -( ) const
    {
        return Vec(-x_, -y_, -z_);
    }

    double Vec::operator []( unsigned idx ) const
    {
        return *(&x_ + idx % 3);
    }

    double Vec::len( ) const
    {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
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
        ist >> v.x_ >> v.y_ >> v.z_;
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
