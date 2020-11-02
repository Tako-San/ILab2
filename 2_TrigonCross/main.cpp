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

    is_intr.resize(N);
    
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

    Vec minv{vmin[0] - 1, vmin[1] - 1, vmin[2] - 1},
        maxv{vmax[0] + 1, vmax[1] + 1, vmax[2] + 1};
    
    OctTree<Triangle> scene{Box(minv, maxv)};

    for (auto t : tr)
        if (!scene.insert(t))
            return 1;

    int idx = 0;
    auto & lst = scene.data_;
    for (auto cur = lst.cbegin(), end = lst.cend(); cur != end; ++cur, ++idx)
    {
        auto & mates = cur->second->data_;

        /*for (ulong i = 0; i < mates.size(); ++i)
        {
            if (is_intersect3D(cur->first, mates[i]->first))
                ++is_intr[idx];
        }*/

    // TODO: рассмотреть случай когда треугольник лежит не в листе, а в промежуточном узле

        //for (auto mate = mates.cbegin(), mend = mates.cend(); mate != mend; ++mate)
        for (auto mate : cur->second->data_)
            if ( mate != cur && is_intersect3D(cur->first, mate->first))
                ++is_intr[idx];
    }



    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}