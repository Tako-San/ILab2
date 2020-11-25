#include "line.h"

namespace Geom
{
    Line::Line( const Vec & orig, const Vec & dir ) : orig{orig}, dir{normalise(dir)}
    {}

    Line::Line( ) : orig{}, dir{}
    {}

    const Vec & Line::get_orig( ) const
    {
        return orig;
    }

    const Vec & Line::get_dir( ) const
    {
        return dir;
    }

    bool Line::is_invalid( )
    {
        return dir == Vec{0};
    }

    void Line::print( )
    {
        orig.print();
        std::cout << " + ";
        dir.print();
        std::cout << " * t";
    }

    std::ostream & operator <<( std::ostream & ost, const Line & ln )
    {
        ost << ln.get_orig() << " + " << ln.get_dir() << " * t";
        return ost;
    }
}