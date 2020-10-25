#include "plane.h"

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