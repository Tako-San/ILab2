#include <iostream>
#include <vector>

// #include "g_obj/triangle.h"

#include "geom/geom.h"
#include "octree/octree.h"

using std::cout;
using std::cin;
using std::endl;

using std::max;

double find_min( const Triangle & tr, uint idx )
{
    double res = tr[0][idx];
    for (int i = 1; i < 3; ++i)
        res = tr[i][idx] < res ? tr[i][idx] : res;
    return res;
}

double find_max( const Triangle & tr, uint idx )
{
    double res = tr[0][idx];
    for (int i = 1; i < 3; ++i)
        res = tr[i][idx] > res ? tr[i][idx] : res;
    return res;
}

int main( )
{
    size_t N;
    cout << "Input number of triangles: ";
    cin >> N;

    std::vector<Triangle> tr{N};
    std::vector<unsigned> is_intr{};

    for (auto elem : is_intr)
        cout << elem;
    
    cout << "Input triangle\n";
    cin >> tr[0];
    
    double vmin[3] = {find_min(tr[0], 0), find_min(tr[0], 1), find_min(tr[0], 2)};
    double vmax[3] = {find_max(tr[0], 0), find_max(tr[0], 1), find_max(tr[0], 2)};
    
    for (unsigned i = 1; i < N; ++i)
    {
        cout << "Input triangle\n";
        cin >> tr[i];
        
        for (int j = 0; j < 3; ++j)
        {
            double cur_min = find_min(tr[i], j);
            double cur_max = find_max(tr[i], j);
            
            vmin[j] = cur_min < vmin[j] ? cur_min : vmin[j];
            vmax[j] = cur_max > vmax[j] ? cur_max : vmax[j];
        }
    }

    Vec minv{vmin[0], vmin[1], vmin[2]},
        maxv{vmax[0], vmax[1], vmax[2]};
    
    OctTree<Triangle> scene{Box(minv, maxv)};

    for (auto t : tr)
        scene.insert(t);

    for (unsigned i = 0; i < N; ++i)
    {
        is_intr.push_back(0);
        auto found = scene.find_box(tr[i]);
        if (found != nullptr)
            for (auto & cur : found->data_)
                if (is_intersect3D(tr[i], *cur) && tr[i] != (*cur))
                    ++is_intr[i];
    }



    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}