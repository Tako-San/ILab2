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

class Triangle;

class Vec
{
private:
    double x, y, z;

    double & get(int idx);

public:
    Vec( double x, double y, double z ) : x(x), y(y), z(z)
    {}

    explicit Vec( double r ) : x(r), y(r), z(r)
    {}

    Vec( ) : Vec{0}
    {}

    Vec( const Vec & v ) = default;


    bool operator == ( const Vec & ) const;
    bool operator != ( const Vec & ) const;

    Vec & normalise( );
    Vec perp2D( ) const;
    void print() const;

    Vec & operator += ( const Vec & );
    Vec & operator -= ( const Vec & );
    Vec & operator *= ( double );
    Vec & operator /= ( double );

    Vec & operator = ( const Vec & );
    Vec operator - ( ) const;

    double len ( ) const;
    double operator [] ( unsigned ) const; // get vector coorinate by number

    friend std::istream & operator >> ( std::istream &, Vec &);
    friend bool is_intersect2D( const Triangle &, const Triangle & );
};

Vec operator + ( const Vec &, const Vec & );
Vec operator - ( const Vec &, const Vec & );
Vec operator * ( const Vec &, double );
Vec operator * ( double, const Vec & );

double operator & ( const Vec &, const Vec & ); // dot product
Vec operator % ( const Vec &, const Vec & );    // cross product

Vec normalise( const Vec & );

std::ostream & operator << ( std::ostream & ost, const Vec & v );

#endif //ILAB2_VEC
