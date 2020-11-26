#ifndef ILAB2_GEOM_H
#define ILAB2_GEOM_H

#include "g_obj/vec.h"
#include "g_obj/box.h"
#include "g_obj/line.h"
#include "g_obj/plane.h"
#include "g_obj/triangle.h"

#include "../octree/octree.hh"

// TODO: tst 33, 26, 25, 24, 21, 15, 9,

namespace Geom
{
    using namespace Octree;
    using std::pair;
    using std::list;

    unsigned ind_of_max( double a, double b, double c );

    bool is_intersect_inv( const Triangle & tr1, const Triangle & tr2 );

    bool is_intersect3D( const Line & l, const Triangle & tr );

    bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 );

    bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 );

    Line intersection( const Plane & pl1, const Plane & pl2 );

    void find_cross( const Triangle & tr, double sd[], const Line & int_line, double t[] );

    bool cmp_seg( double t1[], double t2[] );

    int get_mid_ind( int i0, int i1, int N );

    int get_extreme_ind( const Triangle & tr, const Vec & pt );

    bool tst_intr( const Triangle & tr1, const Triangle & tr2 );

    bool intersect_octree( typename list<pair<Triangle, OctNode<Triangle> *>>::iterator pair_it );
}
#endif //ILAB2_GEOM_H
