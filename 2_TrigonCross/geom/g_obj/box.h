#ifndef TRIANGLES_BOX_H
#define TRIANGLES_BOX_H

#include "vec.h"
#include "triangle.h"

class Box final
{
private:

    Vec min_; // all coords min
    Vec max_; // all coords max

public:

    Box( );
    Box( const Box & ) = default;
    Box( const Vec & min, const Vec & max );
    /*Box( double min_x, double min_y, double min_z,
         double max_x, double max_y, double max_z );*/

    Box & operator = ( const  Box & ) = default;

    bool is_in( const Vec & v ) const;
    bool is_in( const Triangle & tr ) const;

    bool is_invalid( ) const;

    const Vec & get_min( );
    const Vec & get_max( );
};


#endif //TRIANGLES_BOX_H
