#ifndef ILAB2_PLANE_H
#define ILAB2_PLANE_H

#include "vec.h"
#include "line.h"

class Plane
{
private:
    Vec nrm;
    double dst;

public:
    Plane( const Vec & v1, double dst ) : nrm(normalise(v1)), dst(dst)
    {}

    Plane( const Vec & v1, const Vec & v2, const Vec & v3 ) : nrm(normalise((v2 - v1) % (v3 - v1))),
                                                              dst(v1 & nrm)
    {}

    Plane( const Vec & norm, const Vec & p ) : nrm(normalise(norm)),
                                               dst(p & nrm)
    {}

    Plane( const Plane & pl ) = default;

    double sdst( const Vec & pt )
    {
        return (pt & nrm) + dst;
    }

    Vec get_nrm( )
    {
        return nrm;
    }

    double get_dst( )
    {
        return dst;
    }

    static Line intersect( const Plane & pl1, const Plane & pl2 );

    friend std::ostream & operator << ( std::ostream & ost, const Plane & pl )
    {
        ost << "nrm: " << pl.nrm <<
             ", dst: " << pl.dst;

        return ost;
    }
};

Line Plane::intersect( const Plane &pl1, const Plane &pl2 )
{
    return Line(Vec(0), Vec(0));
}

#endif //ILAB2_PLANE_H
