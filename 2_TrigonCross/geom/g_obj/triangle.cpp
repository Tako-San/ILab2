#include "triangle.h"

namespace Geom
{
    LineMap LINE_PT =
            {
                    {LINE12, {0, 1}},
                    {LINE13, {0, 2}}
            };


    Triangle::Triangle( const Vec & v1,
                        const Vec & v2,
                        const Vec & v3 ) : v1_{v1}, v2_{v2}, v3_{v3},
                                           inv_{is_invalid()},
                                           shape_{find_shape()}
    {}

    Triangle::Triangle( ) : v1_{}, v2_{}, v3_{},
                            inv_{is_invalid()},
                            shape_{find_shape()}
    {}

    uint8_t Triangle::find_shape( ) const
    {
        if (!inv_)
            return TRIANGLE;

        uint8_t res = 0u;

        if (v1_ != v2_)
        {
            if (v1_ == v3_ || v2_ == v3_)
                res |= LINE12;
        }
        else if (v1_ == v3_)
            return POINT;
        else
            res |= LINE13;

        return res;
    }

    Plane Triangle::plane( ) const
    {
        if (inv_)
            return POISON_PLANE;
        return Plane(v1_, v2_, v3_);
    }

    const Vec & Triangle::operator []( unsigned idx ) const
    {
        return *(&v1_ + idx % 3);
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

    uint8_t Triangle::shape( ) const
    {
        return shape_;
    }

    double Triangle::min_coord( unsigned idx ) const
    {
        const Triangle & tr = *this;
        double min = tr[0][idx];
        for (int i = 1; i < 3; ++i)
            min = std::min(tr[i][idx], min);
        return min;
    }

    double Triangle::max_coord( unsigned idx ) const
    {
        const Triangle & tr = *this;
        double max = tr[0][idx];
        for (int i = 1; i < 3; ++i)
            max = std::max(tr[i][idx], max);
        return max;
    }

    bool Triangle::is_invalid( ) const
    {
        return (v1_ - v2_) % (v1_ - v3_) == ZERO_VEC;
    }

    bool Triangle::is_point( ) const
    {
        return shape_ & POINT;
    }

    bool Triangle::is_line( ) const
    {
        return shape_ & LINE;
    }

    bool Triangle::is_inv( ) const
    {
        return inv_;
    }

    std::istream & operator >>( std::istream & ist, Triangle & tr )
    {
        ist >> tr.v1_ >> tr.v2_ >> tr.v3_;
        tr.inv_ = tr.is_invalid();
        tr.shape_ = tr.find_shape();
        return ist;
    }
}

std::ostream & operator <<( std::ostream & ost, const Geom::Triangle & tr )
{
    for (int i = 0; i < 3; ++i)
        ost << "v[" << i << "] = " << tr[i] << " ";
    ost << ";";
    return ost;
}

bool operator ==( const Geom::Triangle & lhs, const Geom::Triangle & rhs )
{
    for (int i = 0; i < 3; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

bool operator !=( const Geom::Triangle & lhs, const Geom::Triangle & rhs )
{
    return !(lhs == rhs);
}
