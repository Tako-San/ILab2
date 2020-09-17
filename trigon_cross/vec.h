#ifndef ILAB2_COME_UP_WITH_A_NAME_H
#define ILAB2_COME_UP_WITH_A_NAME_H

#include <iostream>
#include <cmath>

#define ACCURACY 0.0001

struct Vec
{
    double x, y, z;

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

    Vec operator + ( const Vec & ) const;
    Vec operator - ( const Vec & ) const;

    Vec & operator += ( const Vec & );
    Vec & operator -= ( const Vec & );

    Vec & operator = ( const Vec & );
    Vec & operator - ( );

    double operator ! ( ) const;
    Vec operator % ( const Vec &v ) const;

    friend std::ostream & operator << ( std::ostream & ost, const Vec & unit );
};


#endif //ILAB2_COME_UP_WITH_A_NAME_H
