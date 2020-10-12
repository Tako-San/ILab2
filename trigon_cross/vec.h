#ifndef ILAB2_VEC
#define ILAB2_VEC

#include <iostream>
#include <cmath>

#define ACCURACY 0.0001

enum Coords
{
    X = 0,
    Y = 1,
    Z = 2
};

class Vec
{
private:
    double x, y, z;

public:
    Vec( double x, double y, double z ) : x(x), y(y), z(z)
    {}

    explicit Vec( double r = 0 ) : x(r), y(r), z(r)
    {}

    Vec( const Vec & v ) = default;


    bool operator == ( const Vec & ) const;
    bool operator != ( const Vec & ) const;

    Vec & normalise( );

    Vec & operator += ( const Vec & );
    Vec & operator -= ( const Vec & );
    Vec & operator *= ( double );
    Vec & operator /= ( double );

    Vec & operator = ( const Vec & );
    Vec operator - ( ) const;

    double operator [] ( unsigned ) const; // get vector coorinate by number
    double operator ! ( ) const; // vector module

    friend std::ostream & operator << ( std::ostream &, const Vec & );
};

Vec operator + ( const Vec &, const Vec & );
Vec operator - ( const Vec &, const Vec & );
Vec operator * ( const Vec &, double );
Vec operator * ( double, const Vec & );

double operator & ( const Vec &, const Vec & ); // dot product
Vec operator % ( const Vec &, const Vec & );    // cross product

Vec normalise( const Vec & );


#endif //ILAB2_VEC
