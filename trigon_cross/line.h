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

    Vec get_orig( ) const
    {
        return orig;
    }

    Vec get_dir( ) const
    {
        return dir;
    }

    bool is_invalid()
    {
        return dir == Vec{0};
    }

    friend std::ostream & operator << ( std::ostream & ost, const Line & ln )
    {
        ost << ln.orig << " + " << ln.dir << " * t";
        return ost;
    }
};



#endif //ILAB2_LINE_H
