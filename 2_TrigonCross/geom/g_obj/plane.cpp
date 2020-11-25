#include "plane.h"

namespace Geom
{
    const Plane POISON_PLANE{ZERO_VEC, 0};

    Plane::Plane( const Vec & norm, double dist ) : nrm_{normalise(norm)},
                                                   dst_{dist},
                                                   inv_{is_invalid()}
    {}

    Plane::Plane( const Vec & v1,
                  const Vec & v2,
                  const Vec & v3 ) : nrm_{normalise((v2 - v1) % (v3 - v1))},
                                     dst_{v1 & nrm_},
                                     inv_{is_invalid()}
    {}

    Plane::Plane( const Vec & norm, const Vec & p ) : nrm_{normalise(norm)},
                                                      dst_{p & nrm_},
                                                      inv_{is_invalid()}
    {}

    double Plane::sdst( const Vec & pt ) const
    {
        return ((pt & nrm_) - dst_);
    }

    const Vec & Plane::get_nrm( ) const
    {
        return nrm_;
    }

    double Plane::get_dst( ) const
    {
        return dst_;
    }

    bool Plane::is_invalid( ) const
    {
        return nrm_ == ZERO_VEC;
    }

    bool Plane::is_inv( ) const
    {
        return inv_;
    }

    void Plane::print( ) const
    {
        std::cout << "nrm: ";
        nrm_.print();
        std::cout << ", dst: " << dst_;
    }
}

std::ostream & operator <<( std::ostream & ost, const Geom::Plane & pl )
{
    ost << "nrm: " << pl.get_nrm() <<
         ", dst: " << pl.get_dst();
    return ost;
}

