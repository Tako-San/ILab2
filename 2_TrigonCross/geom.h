#include "g_obj/vec.h"
#include "g_obj/line.h"
#include "g_obj/plane.h"
#include "g_obj/triangle.h"

#ifndef ILAB2_GEOM_H
#define ILAB2_GEOM_H

bool is_intersect3D( const Triangle &, const Triangle & );
bool is_intersect2D( const Triangle &, const Triangle & );

Line intersection( const Plane &, const Plane & );

void find_cross( const Triangle &, const double[], const Line &, double[] );
bool cmp_seg(double[], double[]);

int get_mid_ind( int, int, int );
int get_extreme_ind( const Triangle &, const Vec & );
bool tst_intr( const Triangle &, const Triangle & );


#endif //ILAB2_GEOM_H
