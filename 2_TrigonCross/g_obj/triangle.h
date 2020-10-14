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

    Triangle( ) : v1{}, v2{}, v3{}
    {}

    Triangle( const Triangle & tr ) = default;

    Plane plane( ) const
    {
        return Plane(v1, v2, v3);
    }

    const Vec & operator [] ( unsigned idx ) const;

    void print( ) const;

    friend std::istream & operator >> ( std::istream & ist, Triangle & tr );
};

/*std::ostream & operator << ( std::ostream & ost, const Triangle & tr )
{
    for (int i = 0; i < 3; ++i)
        ost << "v[" << i << "] = " << tr[0] << " ";
    ost << ";";
    return ost;
}*/

#endif //ILAB2_TRIANGLE_H
