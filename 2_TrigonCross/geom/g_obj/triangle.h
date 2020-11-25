#ifndef ILAB2_TRIANGLE_H
#define ILAB2_TRIANGLE_H

#include <map>

#include "vec.h"
#include "plane.h"

namespace Geom
{
    enum DegenT
    {
        TRIANGLE = 1u,
        POINT    = 1u << 1u,
        LINE12   = 1u << 2u,
        LINE13   = 1u << 3u,
        LINE = LINE12 | LINE13
    };

    using std::map;
    using std::pair;

    using LineMap = map<DegenT, pair<uint, uint>>;

    extern LineMap LINE_PT;

    class Triangle final
    {
    private:
        Vec v1_, v2_, v3_;
        bool inv_;
        uint8_t shape_;

        uint8_t find_shape( ) const;
    public:

        Triangle( );
        Triangle( const Vec & v1, const Vec & v2, const Vec & v3 );

        Plane plane( ) const;

        const Vec & operator []( unsigned idx ) const;

        void print( ) const;

        uint8_t shape( ) const;

        double min_coord( unsigned idx ) const;
        double max_coord( unsigned idx ) const;

        bool is_invalid( ) const;
        bool is_point( ) const;
        bool is_line( ) const;
        bool is_inv( ) const;

        friend std::istream & operator >>( std::istream & ist, Triangle & tr );
    };
}

std::ostream & operator <<( std::ostream & ost, const Geom::Triangle & tr );

bool operator ==( const Geom::Triangle & lhs, const Geom::Triangle & rhs );
bool operator !=( const Geom::Triangle & lhs, const Geom::Triangle & rhs );

#endif //ILAB2_TRIANGLE_H
