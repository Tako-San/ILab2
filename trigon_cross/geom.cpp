#include "vec.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"

#include "geom.h"

using std::abs;
using std::swap;
using std::cout;
using std::endl;

const Vec ZERO_VEC{0};
const Line INVALID_LINE{ZERO_VEC, ZERO_VEC};


bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 )
{
    Plane pl1 = tr1.plane();
    Plane pl2 = tr2.plane();


    if (pl1.get_nrm() % pl2.get_nrm() == ZERO_VEC &&
        abs(pl1.get_dst()) == abs(pl2.get_dst()))
        return is_intersect2D(tr1, tr2); // TODO: написать

    double sd2[3] = {};
    double sd1[3] = {};

    for (int i = 0; i < 3; ++i)
    {
        sd2[i] = pl1.sdst(tr2[i]);
        sd1[i] = pl2.sdst(tr1[i]);
    }

    if (((sd1[0] * sd1[1] >= 0) &&
         (sd1[0] * sd1[2] >= 0) &&
         (sd1[1] * sd1[2] >= 0)))
        return false;

    if (((sd2[0] * sd2[1] >= 0) &&
         (sd2[0] * sd2[2] >= 0) &&
         (sd2[1] * sd2[2] >= 0)))
        return false;

    Line int_line = intersection(pl1, pl2);

    if (int_line.is_invalid())
        return false;

    double t1[2] = {};
    double t2[2] = {};

    find_cross(tr1, sd1, int_line, t1);
    find_cross(tr2, sd2, int_line, t2);

    return cmp_seg(t1, t2);
}


bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 )
{
    cout << "FUNC: " << __PRETTY_FUNCTION__ << "\n\n";



    return false;
}


Line intersection( const Plane & pl1, const Plane & pl2 )
{
    Vec n1 = pl1.get_nrm(),
        n2 = pl2.get_nrm();

    Vec n1n2_cross = n1 % n2;

    if (n1n2_cross == ZERO_VEC)
        return INVALID_LINE;

    double s1 = pl1.get_dst(),
           s2 = pl2.get_dst();

    double n1n2 = n1 & n2,
           n1_2 = n1 & n1,
           n2_2 = n2 & n2;

    double a = (s2 * n1n2 - s1 * n2_2) / (n1n2 * n1n2 - n1_2 * n2_2);
    double b = (s1 * n1n2 - s2 * n1_2) / (n1n2 * n1n2 - n1_2 * n2_2);

    return Line{a * n1 + b * n2, n1n2_cross};
}


void find_cross( const Triangle & tr, const double sd[], const Line & int_line, double t[] )
{
    int rg, /* rogue */
        m0, /* mate0 */
        m1; /* mate1 */

    if ((sd[0] * sd[1]) >= 0)
        rg = 2;
    else if ((sd[1] * sd[2]) >= 0)
        rg = 0;
    else
        rg = 1;

    m0 = (rg + 1) % 3;
    m1 = (rg + 2) % 3;

    double pr[3] = {};

    for (int i = 0; i < 3; ++i)
        pr[i] = int_line.get_dir() & (tr[i] - int_line.get_orig());

    t[0] = pr[m0] + (pr[rg] - pr[m0]) * sd[m0] / (sd[m0] - sd[rg]);
    t[1] = pr[m1] + (pr[rg] - pr[m1]) * sd[m1] / (sd[m1] - sd[rg]);
}


bool cmp_seg(double t1[], double t2[])
{
    if (t1[0] > t1[1])
        swap(t1[0], t1[1]);

    if (t2[0] > t2[1])
        swap(t2[0], t2[1]);

    return !((t1[1] < t2[0]) || (t1[0] > t2[1]));
}