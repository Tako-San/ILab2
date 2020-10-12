#include "vec.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"

bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 );
bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 );

Line intersection( const Plane & pl1, const Plane & pl2 );
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

    Vec nrm1 = pl1.get_nrm(),
        nrm2 = pl2.get_nrm();

    double dst1 = std::abs(pl1.get_dst()),
           dst2 = std::abs(pl2.get_dst());

    if (((nrm1 == nrm2) || (nrm1 == -nrm2)) && (dst1 == dst2))
        return is_intersect2D(tr1, tr2);

    double sdst21 = pl2.sdst(tr1[1]),
           sdst22 = pl2.sdst(tr1[2]),
           sdst23 = pl2.sdst(tr1[3]);

    if (!((sdst21 * sdst22 >= 0) && (sdst21 * sdst23 >= 0) && (sdst22 * sdst23 >= 0)))
        return false;

    Line int_line = intersection(pl1, pl2);

    return lst_fnc_idk_how_2_call_it(tr1, tr2, int_line);
}

bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return false;
}

Line intersection( const Plane & pl1, const Plane & pl2 )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return Line{};
}

bool lst_fnc_idk_how_2_call_it( const Triangle & tr1, const Triangle & tr2, const Line & int_line )
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return false;
}