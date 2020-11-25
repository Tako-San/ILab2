#ifndef ILAB2_TRIANGLE_H
#define ILAB2_TRIANGLE_H

#include "vec.h"
#include "plane.h"

namespace Geom
{
    class Triangle final
    {
    private:
        Vec v1, v2, v3;

    public:

        Triangle( );
        Triangle( const Vec & v1, const Vec & v2, const Vec & v3 );

        Plane plane( ) const;

        const Vec & operator []( unsigned idx ) const;

        void print( ) const;

        double min_coord( unsigned idx ) const;
        double max_coord( unsigned idx ) const;

        friend std::istream & operator >>( std::istream & ist, Triangle & tr );
    };

    std::ostream & operator <<( std::ostream & ost, const Triangle & tr );

    bool operator ==( const Triangle & lhs, const Triangle & rhs );

    bool operator !=( const Triangle & lhs, const Triangle & rhs );
}
#endif //ILAB2_TRIANGLE_H
