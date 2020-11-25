#ifndef ILAB2_PLANE_H
#define ILAB2_PLANE_H

#include "vec.h"

namespace Geom
{
    class Plane final
    {
    private:
        Vec nrm;
        double dst;

    public:
        Plane( const Vec & norm, double dst );

        Plane( const Vec & v1, const Vec & v2, const Vec & v3 );

        Plane( const Vec & norm, const Vec & p );

        double sdst( const Vec & pt ) const;

        const Vec & get_nrm( ) const;

        double get_dst( ) const;

        void print( ) const;
    };
}

std::ostream & operator <<( std::ostream & ost, const Geom::Plane & pl );

#endif //ILAB2_PLANE_H
