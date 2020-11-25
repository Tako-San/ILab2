#ifndef ILAB2_LINE_H
#define ILAB2_LINE_H

#include "vec.h"

namespace Geom
{
    class Line final
    {
    private:
        Vec orig_, dir_;

        bool inv_;

    public:

        Line( );
        Line( const Vec & orig, const Vec & dir );

        const Vec & get_orig( ) const;
        const Vec & get_dir( ) const;

        bool is_invalid( ) const;
        bool is_inv( ) const;
        bool is_intr( const Line & l ) const;
        bool belongs( const Vec & v ) const;

        void print( );
    };

    bool line_intr( const Line & l1, const Line & l2 );
    bool is_on_line( const Line & l, const Vec & v);

    extern const Line POISON_LINE;
}

std::ostream & operator <<( std::ostream &, const Geom::Line & );

#endif //ILAB2_LINE_H
