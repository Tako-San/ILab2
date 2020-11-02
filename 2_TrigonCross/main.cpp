#include <iostream>
#include <vector>

// #include "g_obj/triangle.h"

#include "geom/geom.h"
#include "octree/octree.h"

using std::cout;
using std::cin;
using std::endl;

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

bool intersect_subtree( OctNode<Triangle> & node, Triangle obj)
{
    for (auto mate : node.data_)
        if (is_intersect3D(obj, mate->first))
            return true;

    if (node.has_children)
        for (auto ch : node.child_)
            if (intersect_subtree(*ch, obj))
                return true;

    return false;
}


bool intersect_octree( typename list<pair<Triangle, OctNode<Triangle> *>>::iterator pair_it )
{
    OctNode<Triangle> & node = *(pair_it->second);
    Triangle & obj = pair_it->first;

    for (auto mate : node.data_)
        if (mate != pair_it && is_intersect3D(obj, mate->first))
            return true;

    if (node.has_children)
        for (auto ch : node.child_)
            if (intersect_subtree(*ch, obj))
                return true;

    return false;
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
    for (auto cur = lst.begin(), end = lst.end(); cur != end; ++cur, ++idx)
    {
        auto & node = *(cur->second);
        for (auto mate : node.data_)
            if (intersect_octree(cur))
                ++is_intr[idx];
    }



    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}