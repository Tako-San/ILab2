#include <iostream>
#include <vector>

#include "geom/geom.h"
#include "octree/octree.h"

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
    cin >> tr[0];
    
    double vmin[3] = {tr[0].min_coord(X), tr[0].min_coord(Y), tr[0].min_coord(Z)};
    double vmax[3] = {tr[0].max_coord(X), tr[0].max_coord(Y), tr[0].max_coord(Z)};
    
    for (unsigned i = 1; i < N; ++i)
    {
        cin >> tr[i];
        
        for (int j = 0; j < 3; ++j)
        {
            double cur_min = tr[i].min_coord(j);
            double cur_max = tr[i].max_coord(j);
            
            vmin[j] = cur_min < vmin[j] ? cur_min : vmin[j];
            vmax[j] = cur_max > vmax[j] ? cur_max : vmax[j];
        }
    }

    // create octree
    Vec minv{vmin[0] - 1, vmin[1] - 1, vmin[2] - 1},
        maxv{vmax[0] + 1, vmax[1] + 1, vmax[2] + 1};
    
    OctTree<Triangle> scene{Box(minv, maxv)};

    for (auto t : tr)
        if (!scene.insert(t))
            return 1;

    // check intersections
    int idx = 0;
    auto & lst = scene.data_;
    for (auto cur = lst.begin(), end = lst.end(); cur != end; ++cur, ++idx)
        if (intersect_octree(cur))
            ++is_intr[idx];

    // output
    uint count = 0;

    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}