#ifndef ILAB2_LINE_H
#define ILAB2_LINE_H

#include "vec.h"


class Line
{
private:
    Vec orig, dir;

public:
    Line( const Vec & r1, const Vec & r2 ) : orig(r1), dir(r2 - r1)
    {}

    Line( const Line & l ) = default;

    friend std::ostream & operator << ( std::ostream & ost, const Line & ln )
    {
        ost << ln.orig << " + " << ln.dir << " * t";
        return ost;
    }
};


#endif //ILAB2_LINE_H
