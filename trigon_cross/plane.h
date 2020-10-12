#ifndef ILAB2_PLANE_H
#define ILAB2_PLANE_H

#include "vec.h"
#include "line.h"

class Plane
{
private:
    Vec norm;
    double dist;

public:
    Plane( const Vec & v1, double dist ) : norm(normalise(v1)), dist(dist)
    {}

    Plane( const Vec & v1, const Vec & v2, const Vec & v3 ) :
    {}
};

#endif //ILAB2_PLANE_H
