#ifndef ILAB2_GEOM_H
#define ILAB2_GEOM_H

bool is_intersect3D( const Triangle &, const Triangle & );
bool is_intersect2D( const Triangle &, const Triangle & );

Line intersection( const Plane &, const Plane & );
bool is_parallel( const Plane &, const Plane & );

void find_cross( const Triangle &, const double[], const Line &, double[] );
bool cmp_seg(double[], double[]);


#endif //ILAB2_GEOM_H
