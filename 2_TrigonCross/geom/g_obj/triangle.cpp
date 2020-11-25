#include "triangle.h"

namespace Geom
{
    Triangle::Triangle( const Vec & v1, const Vec & v2, const Vec & v3 ) : v1{v1}, v2{v2}, v3{v3}
    {}

    Triangle::Triangle( ) : v1{}, v2{}, v3{}
    {}

    Plane Triangle::plane( ) const
    {
        return Plane(v1, v2, v3);
    }

    const Vec & Triangle::operator []( unsigned idx ) const
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

    double Triangle::min_coord( unsigned idx ) const
    {
        const Triangle & tr = *this;
        double res = tr[0][idx];
        for (int i = 1; i < 3; ++i)
            res = tr[i][idx] < res ? tr[i][idx] : res;
        return res;
    }

    double Triangle::max_coord( unsigned idx ) const
    {
        const Triangle & tr = *this;
        double res = tr[0][idx];
        for (int i = 1; i < 3; ++i)
            res = tr[i][idx] > res ? tr[i][idx] : res;
        return res;
    }


    std::istream & operator >>( std::istream & ist, Triangle & tr )
    {
        ist >> tr.v1 >> tr.v2 >> tr.v3;
        return ist;
    }

    std::ostream & operator <<( std::ostream & ost, const Triangle & tr )
    {
        for (int i = 0; i < 3; ++i)
            ost << "v[" << i << "] = " << tr[i] << " ";
        ost << ";";
        return ost;
    }

    bool operator ==( const Triangle & lhs, const Triangle & rhs )
    {
        for (int i = 0; i < 3; ++i)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    bool operator !=( const Triangle & lhs, const Triangle & rhs )
    {
        return !(lhs == rhs);
    }
}
