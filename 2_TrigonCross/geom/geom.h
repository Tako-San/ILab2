#ifndef ILAB2_GEOM_H
#define ILAB2_GEOM_H

#include "g_obj/vec.h"
#include "g_obj/box.h"
#include "g_obj/line.h"
#include "g_obj/plane.h"
#include "g_obj/triangle.h"

namespace Geom
{
    template <typename T>
    int sign( T value );

    bool inv_trian_intr( const Triangle & tr1, const Triangle & tr2 );
    bool trian_line_intr3D( const Line & l, const Triangle & tr );
    bool trian_intr3D( const Triangle & tr1, const Triangle & tr2 );
    bool trian_intr2D( const Triangle & tr1, const Triangle & tr2 );
    Line intersection( const Plane & pl1, const Plane & pl2 );
    bool tst_intr( const Triangle & tr1, const Triangle & tr2 );

    std::array<double, 2> find_t_param( const Triangle & tr, const Line & int_line, std::array<double, 3> sd );
    bool cmp_seg( std::array<double, 2> t1, std::array<double, 2> t2 );

    uint ind_of_max( double a, double b, double c );
    uint get_mid_ind( int i0, int i1, int N );
    uint get_extreme_ind( const Triangle & tr, const Vec & pt );
}
#endif //ILAB2_GEOM_H
