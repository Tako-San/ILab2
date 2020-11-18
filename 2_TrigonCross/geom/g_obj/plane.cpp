#include "plane.h"

Plane::Plane( const Vec & norm, double dst ) : nrm{normalise(norm)},
                                               dst{dst}
{}

Plane::Plane( const Vec & v1, const Vec & v2, const Vec & v3 ) : nrm{normalise((v2 - v1) % (v3 - v1))},
                                                                 dst{v1 & nrm}
{}

Plane::Plane( const Vec & norm, const Vec & p ) : nrm{normalise(norm)},
                                                  dst{p & nrm}
{}

double Plane::sdst( const Vec & pt ) const
{
    return ((pt & nrm) - dst);
}

const Vec & Plane::get_nrm( ) const
{
    return nrm;
}

double Plane::get_dst( ) const
{
    return dst;
}

void Plane::print() const
{
    std::cout << "nrm: ";
    nrm.print();
    std::cout << ", dst: " << dst;
}

std::ostream & operator << ( std::ostream & ost, const Plane & pl )
{
    ost << "nrm: " << pl.get_nrm() <<
        ", dst: " << pl.get_dst();
    return ost;
}