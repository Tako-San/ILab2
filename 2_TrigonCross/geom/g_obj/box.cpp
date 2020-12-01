#include "box.h"

namespace Geom
{
    Box::Box( ) : min_(),
                  max_()
    {}

    Box::Box( const Vec & min,
              const Vec & max ) : min_(min),
                                  max_(max)
    {}

    template <typename Obj>
    bool Box::is_in( const Obj & obj ) const
    {
        return false;
    }

#define LS_MAX( idx )        \
    (obj[idx] < max_[idx])   \

#define GR_MIN( idx )        \
    (obj[idx] > min_[idx])   \


    template <>
    bool Box::is_in( const Vec & obj ) const
    {
        return LS_MAX(X) && LS_MAX(Y) && LS_MAX(Z) &&
               GR_MIN(X) && GR_MIN(Y) && GR_MIN(Z);
    }

#undef LS_MAX
#undef GR_MIN

    template <>
    bool Box::is_in( const Triangle & obj ) const
    {
        return is_in(obj[0]) && is_in(obj[1]) && is_in(obj[2]);
    }

#define MIN_VS_MAX( idx )        \
        (min_[idx] <= max_[idx]) \

    bool Box::is_invalid( ) const
    {
        return MIN_VS_MAX(X) && MIN_VS_MAX(Y) && MIN_VS_MAX(Z);
    }

#undef MIN_VS_MAX

    const Vec & Box::get_min( ) const
    {
        return min_;
    }

    const Vec & Box::get_max( ) const
    {
        return max_;
    }

    double Box::diag( ) const
    {
        return Vec{max_ - min_}.len();
    }

    std::ostream & operator <<( std::ostream & ost, const Geom::Box & box )
    {
        ost << "min = " << box.get_min() << ", max = " << box.get_max();
        return ost;
    }
}