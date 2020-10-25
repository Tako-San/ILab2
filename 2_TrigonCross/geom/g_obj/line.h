#ifndef ILAB2_LINE_H
#define ILAB2_LINE_H

#include "vec.h"


class Line
{
private:
    Vec orig, dir;

public:
    Line( const Vec & orig, const Vec & dir ) : orig(orig), dir(normalise(dir))
    {}

    Line( ) : orig(Vec{}), dir(Vec{})
    {}

    Line( const Line & l ) = default;

    const Vec & get_orig( ) const;
    const Vec & get_dir( ) const;

    bool is_invalid();
    void print( );
};

std::ostream & operator << ( std::ostream &, const Line & );

#endif //ILAB2_LINE_H
