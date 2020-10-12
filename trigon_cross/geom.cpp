#include "vec.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"

const Vec ZERO_VEC{0};
const Line INVALID_LINE{ZERO_VEC, ZERO_VEC};

bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 );
bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 );

Line intersection( const Plane & pl1, const Plane & pl2 );
bool is_parallel( const Plane & pl1, const Plane & pl2 );
bool lst_fnc_idk_how_2_call_it( const Triangle & tr1, const Triangle & tr2, const Line & int_line );

bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 )
{
    Plane pl1 = tr1.plane();

    double sdst11 = pl1.sdst(tr2[0]),
           sdst12 = pl1.sdst(tr2[1]),
           sdst13 = pl1.sdst(tr2[2]);

    if (((sdst11 * sdst12 >= 0) && (sdst11 * sdst13 >= 0) && (sdst12 * sdst13 >= 0)))
        return false;

    Plane pl2 = tr2.plane();

    if (pl1 == pl2)
        return is_intersect2D(tr1, tr2); // TODO: написать

    double sdst21 = pl2.sdst(tr1[1]),
           sdst22 = pl2.sdst(tr1[2]),
           sdst23 = pl2.sdst(tr1[3]);

    if (!((sdst21 * sdst22 >= 0) && (sdst21 * sdst23 >= 0) && (sdst22 * sdst23 >= 0)))
        return false;

    Line int_line = intersection(pl1, pl2); // TODO: написать

    return lst_fnc_idk_how_2_call_it(tr1, tr2, int_line); // TODO: написать
}

bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return false;
}

bool is_parallel( const Plane & pl1, const Plane & pl2 )
{
    return (pl1.get_nrm() % pl2.get_nrm() == ZERO_VEC);
}

Line intersection( const Plane & pl1, const Plane & pl2 )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";

    Vec n1 = pl1.get_nrm(),
        n2 = pl2.get_nrm();

    Vec n1n2_cross = n1 % n2;

    if (n1n2_cross == ZERO_VEC)
        return INVALID_LINE;

    double s1 = pl1.get_dst(),
           s2 = pl2.get_dst();

    double n1n2 = n1 & n2,
           n1p2 = n1 & n1,
           n2p2 = n2 & n2;

    double a{}, b{};

    a = (s2 * n1n2 - s1 * n2p2) / (n1n2 * n1n2 - n1p2 * n2p2);
    b = (s1 * n1n2 - s1 * n2p2) / (n1n2 * n1n2 - n1p2 * n2p2);

    return Line{a * n1 + b * n2, n1n2_cross};
}

bool lst_fnc_idk_how_2_call_it( const Triangle & tr1, const Triangle & tr2, const Line & int_line )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return false;
}