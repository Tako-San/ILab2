#include "line.h"

namespace Geom
{
    const Line POISON_LINE{0, 0};

    Line::Line( ) : orig_{},
                    dir_{},
                    inv_{true}
    {}

    Line::Line( const Vec & orig, const Vec & dir ) : orig_{orig},
                                                      dir_{normalise(dir)},
                                                      inv_{is_invalid()}
    {}

    const Vec & Line::get_orig( ) const
    {
        return orig_;
    }

    const Vec & Line::get_dir( ) const
    {
        return dir_;
    }

    bool Line::is_invalid( ) const
    {
        return dir_ == ZERO_VEC;
    }

    bool Line::is_inv( ) const
    {
        return inv_;
    }

    bool Line::is_intr( const Line & l ) const
    {
        return (std::abs(Vec{l.orig_ - orig_} & (l.dir_ % dir_)) < ACCURACY);
    }

    bool Line::belongs( const Vec & v ) const
    {
        return (v - orig_) % dir_ == ZERO_VEC;
    }

    void Line::print( )
    {
        orig_.print();
        std::cout << " + ";
        dir_.print();
        std::cout << " * t";
    }

    bool line_intr( const Line & l1, const Line & l2 )
    {
        return l1.is_intr(l2);
    }

    bool is_on_line( const Line & l, const Vec & v)
    {
        return l.belongs(v);
    }
}

std::ostream & operator <<( std::ostream & ost, const Geom::Line & ln )
{
    ost << ln.get_orig() << " + " << ln.get_dir() << " * t";
    return ost;
}
