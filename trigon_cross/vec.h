#ifndef ILAB2_VEC
#define ILAB2_VEC

#include <iostream>
#include <cmath>

#define ACCURACY 0.0001

class Vec
{
private:
    double x, y, z;

public:
    Vec( double x, double y, double z ) : x(x),
                                          y(y),
                                          z(z)
    {}

    Vec( const Vec & unit ) : x(unit.x),
                              y(unit.y),
                              z(unit.z)
    {}


    explicit Vec( double r ) : x(r),
                               y(r),
                               z(r)
    {}

    bool operator == ( const Vec & ) const;

    Vec & normalise( );

    Vec & operator += ( const Vec & );
    Vec & operator -= ( const Vec & );
    Vec & operator *= ( double );
    Vec & operator /= ( double );

    Vec & operator = ( const Vec & );
    Vec operator - ( );

    double operator ! ( ) const; // vector module

    friend double operator & ( const Vec &, const Vec & ); // dot product
    friend Vec operator % ( const Vec &, const Vec & );    // cross product
    friend Vec operator + ( const Vec &, const Vec & );
    friend Vec operator - ( const Vec &, const Vec & );

    friend Vec operator * ( const Vec &, double );
    friend Vec operator * ( double, const Vec & );

    friend Vec normalise( const  Vec & );

    friend std::ostream & operator << ( std::ostream & ost, const Vec & unit );
};


#endif //ILAB2_VEC
