#include <iostream>
#include <vector>

#include "geom/geom.h"
#include "octree.hh"

using namespace Geom;

using std::cout;
using std::cin;
using std::endl;


int main( )
{
    // init
    size_t N;
    cin >> N;

    std::vector<Triangle> tr{N};
    std::vector<unsigned> is_intr{};
    is_intr.resize(N);

    // input

    Vec vmin{0},
        vmax{0};

    for (unsigned i = 0; i < N; ++i)
    {
        cin >> tr[i];

        for (int j = 0; j < 3; ++j)
        {
            double cur_min = tr[i].min_coord(j);
            double cur_max = tr[i].max_coord(j);
            
            vmin[j] = std::min(vmin[j], cur_min);
            vmax[j] = std::max(vmax[j], cur_max);
        }
    }

    for (int i = 0; i < 3; ++i)
        vmin[i] -= 1, vmax[i] += 1;

    // create octree
    OctTree<Triangle> scene{Box{vmin, vmax}, tr.begin(), tr.end()};

    // check intersections
    int idx = 0;
    for (auto cur = tr.begin(), end = tr.end(); cur != end; ++cur, ++idx)
        if (scene.is_intersect(*cur))
            ++is_intr[idx];

    // output
    uint count = 0;

    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
        {
            ++count;
            cout << i << endl;
        }

    //cout << "count: " << count << endl;

    //scene.print();
    return 0;
}