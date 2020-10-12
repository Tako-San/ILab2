#ifndef ILAB2_LINE_H
#define ILAB2_LINE_H

#include "vec.h"


class Line
{
private:
    Vec orig, dir;

public:
    Line( const Vec & v1, const Vec & v2 ) : orig(v1), dir(v2 - v1)
    {}

    Line( ) : orig(Vec{}), dir(Vec{})
    {}

    Line( const Line & l ) = default;

    friend std::ostream & operator << ( std::ostream & ost, const Line & ln )
    {
        ost << ln.orig << " + " << ln.dir << " * t";
        return ost;
    }
};



#endif //ILAB2_LINE_H
