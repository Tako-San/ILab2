#ifndef ILAB2_VEC
#define ILAB2_VEC

#include <iostream>
#include <cmath>

namespace Geom
{
    #define ACCURACY 1e-6

    enum Coords
    {
        X = 0,
        Y = 1,
        Z = 2
    };

    class Triangle;

    struct Vec final
    {
        double x_, y_, z_;

        Vec( double x, double y, double z );
        Vec( double r = 0 );

        bool operator==( const Vec & v ) const;
        bool operator!=( const Vec & v ) const;

        Vec & normalise( );

        [[nodiscard]] Vec perp2D( ) const;

        void print( ) const;

        Vec & operator+=( const Vec & v );
        Vec & operator-=( const Vec & v );
        Vec & operator*=( double num );
        Vec & operator/=( double num );

        Vec operator-( ) const;

        [[nodiscard]] double len( ) const;

        double operator[]( unsigned idx ) const; // get vector coorinate by number
        double & operator[]( unsigned idx );

        friend std::istream & operator>>( std::istream & ist, Vec & v );
    };

    extern const Vec ZERO_VEC;

    Vec operator+( const Vec & v1, const Vec & v2 );
    Vec operator-( const Vec & v1, const Vec & v2 );
    Vec operator*( const Vec & v, double num );
    Vec operator*( double num, const Vec & v );

    Vec operator%( const Vec & v1, const Vec & v2 );    // cross product
    double operator&( const Vec & v1, const Vec & v2 ); // dot product

    Vec normalise( const Vec & v );

    std::ostream & operator<<( std::ostream & ost, const Vec & v );
}
#endif //ILAB2_VEC
