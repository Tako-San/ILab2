#ifndef ILAB2_TRIANGLE_H
#define ILAB2_TRIANGLE_H

#include "vec.h"
#include "plane.h"

class Triangle
{
private:
    Vec v1, v2, v3;

public:
    Triangle( const Vec & v1, const Vec & v2, const Vec & v3 ) : v1(v1), v2(v2), v3(v3)
    {}

    Triangle( const Triangle & tr ) = default;

    Plane plane( ) const
    {
        return Plane(v1, v2, v3);
    }

    bool intersect_3D ( const Triangle & tr1, const Triangle & tr2 );
    bool intersect_2D ( const Triangle & tr1, const Triangle & tr2 );
};

#endif //ILAB2_TRIANGLE_H
