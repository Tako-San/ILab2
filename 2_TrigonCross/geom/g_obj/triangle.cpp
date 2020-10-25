#include "triangle.h"


Plane Triangle::plane( ) const
{
    return Plane(v1, v2, v3);
}

const Vec & Triangle::operator [] ( unsigned idx ) const
{
    return *(&v1 + idx % 3);
}

void Triangle::print( ) const
{
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "v[" << i << "] = ";
        (*this)[0].print();
        std::cout << " ";
    }
    std::cout << ";";
}


std::istream & operator >> ( std::istream & ist, Triangle & tr )
{
    ist >> tr.v1 >> tr.v2 >> tr.v3;
    return ist;
}

std::ostream & operator << ( std::ostream & ost, const Triangle & tr )
{
    for (int i = 0; i < 3; ++i)
        ost << "v[" << i << "] = " << tr[0] << " ";
    ost << ";";
    return ost;
}
