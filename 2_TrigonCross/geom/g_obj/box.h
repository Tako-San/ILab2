#ifndef TRIANGLES_BOX_H
#define TRIANGLES_BOX_H

#include "vec.h"
#include "triangle.h"

namespace Geom
{
    class Box final
    {
    private:

        Vec min_; // all coords min
        Vec max_; // all coords max

    public:

        Box( );
        Box( const Vec & min, const Vec & max );

        bool is_in( const Vec & v ) const;
        bool is_in( const Triangle & tr ) const;

        bool is_invalid( ) const;

        const Vec & get_min( ) const;
        const Vec & get_max( ) const;

        double diag( ) const;
    };
}

std::ostream & operator <<( std::ostream & ost, const Geom::Box & box );

#endif //TRIANGLES_BOX_H
