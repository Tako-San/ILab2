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

    double sdst( const Vec & pt ) const
    {
        return ((pt & nrm) - dst);
    }

    const Vec & get_nrm( ) const
    {
        return nrm;
    }

    double get_dst( ) const
    {
        return dst;
    }
};

std::ostream & operator << ( std::ostream & ost, const Plane & pl )
{
    ost << "nrm: " << pl.get_nrm() <<
         ", dst: " << pl.get_dst();
    return ost;
}

#endif //ILAB2_PLANE_H
