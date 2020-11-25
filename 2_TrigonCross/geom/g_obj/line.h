#ifndef ILAB2_LINE_H
#define ILAB2_LINE_H

#include "vec.h"

namespace Geom
{
    class Line final
    {
    private:
        Vec orig, dir;

    public:

        Line( );
        Line( const Vec & orig, const Vec & dir );

        const Vec & get_orig( ) const;
        const Vec & get_dir( ) const;

        bool is_invalid( );

        void print( );
    };

    std::ostream & operator <<( std::ostream &, const Line & );
}
#endif //ILAB2_LINE_H
