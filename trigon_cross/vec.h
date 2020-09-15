#ifndef ILAB2_COME_UP_WITH_A_NAME_H
#define ILAB2_COME_UP_WITH_A_NAME_H

#include <iostream>
#include <cmath>

struct Vec
{
    double x, y, z;

    Vec( double x, double y, double z ) : x(x),
                                          y(y),
                                          z(z)
    {}

    explicit Vec( double r ) : x(r),
                               y(r),
                               z(r)
    {}


    bool operator == ( const Vec & );
    friend std::ostream & operator << ( std::ostream &, const Vec & );
};

bool Vec::operator==( const Vec & that )
{
    return (this->x == that.x) && (this->y == that.y) && (this->z == that.z);
}




#endif //ILAB2_COME_UP_WITH_A_NAME_H
