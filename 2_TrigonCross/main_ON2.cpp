#include <iostream>
#include <vector>

#include "geom/geom.h"

using namespace Geom;
using namespace Octree;

using std::cout;
using std::cin;
using std::endl;

int main( )
{
    unsigned N;
    //cout << "Input number of triangles: ";
    cin >> N;

    std::vector<Triangle> tr;
    std::vector<unsigned> is_intr;

    tr.reserve(N);

    is_intr.reserve(N);
    for (uint i = 0; i < N; ++i)
        is_intr.push_back(0);

    for (unsigned i = 0; i < N; ++i)
    {
        Triangle tmp;
        //cout << "Input triangle\n";
        cin >> tmp;
        tr.emplace_back(tmp);
    }

    for (unsigned i = 0; i < N; ++i)
        for (unsigned j = i + 1; j < N; ++j)
            if (is_intersect3D(tr[i], tr[j]))
            {
                ++is_intr[i];
                ++is_intr[j];
            }

    int count = 0;

    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
        {
            ++count;
            cout << i << endl;
        }

    //cout << count << endl;

    return 0;
}