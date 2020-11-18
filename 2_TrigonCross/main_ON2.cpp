#include <iostream>
#include <vector>

#include "geom/geom.h"

using std::cout;
using std::cin;
using std::endl;

int main( )
{
    unsigned N;
    //cout << "Input number of triangles: ";
    cin >> N;

    std::vector<Triangle> tr{};
    std::vector<unsigned> is_intr = {0};

    tr.resize(N);

    for (unsigned i = 0; i < N; ++i)
    {
        //cout << "Input triangle\n";
        cin >> tr[i];
    }

    cout << "tr num: " << tr.size() << endl;

    for (unsigned i = 0; i < N; ++i)
        for (unsigned j = i + 1; j < N; ++j)
            if (is_intersect3D(tr[i], tr[j]))
            {
                ++is_intr[i];
                ++is_intr[j];
            }

    for (unsigned i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}