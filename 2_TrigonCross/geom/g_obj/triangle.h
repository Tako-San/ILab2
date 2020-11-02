#ifndef ILAB2_TRIANGLE_H
#define ILAB2_TRIANGLE_H

#include "vec.h"
#include "plane.h"

class Triangle final
{
private:
    Vec v1, v2, v3;

public:
    Triangle( const Vec & v1, const Vec & v2, const Vec & v3 ) : v1(v1), v2(v2), v3(v3)
    {}

    Triangle( ) : v1{}, v2{}, v3{}
    {}

    Triangle( const Triangle & tr ) = default;

    Plane plane( ) const;

    const Vec & operator [] ( unsigned idx ) const;

    void print( ) const;

    friend std::istream & operator >> ( std::istream & ist, Triangle & tr );
};

std::ostream & operator << ( std::ostream & ost, const Triangle & tr );
bool operator == ( const Triangle & lhs, const Triangle & rhs);
bool operator != ( const Triangle & lhs, const Triangle & rhs);

#endif //ILAB2_TRIANGLE_H
