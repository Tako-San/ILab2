#include "vec.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"

bool Triangle::intersect_3D ( const Triangle & tr1, const Triangle & tr2 )
{
    Plane pl1 = tr1.plane();
    Plane pl2 = tr2.plane();

    if (pl1.get_nrm() == pl2.get_nrm())
    {
        if (pl1.get_dst() != pl2.get_dst())
            return false;
        else
            return Triangle::intersect_2D(tr1, tr2);
    }
    else
    {
        double dst1 = pl1.sdst(tr1.v1),
               dst2 = pl1.sdst(tr1.v2),
               dst3 = pl1.sdst(tr1.v3);

        if (!((dst1 * dst2 >= 0) && (dst1 * dst3 >= 0) && (dst2 * dst3 >= 0)))
            return false;

        Line int_line = Plane::intersect(pl1, pl2);
    }
}