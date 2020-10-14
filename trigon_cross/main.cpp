#include <iostream>
#include <vector>

#include "vec.h"
#include "line.h"
#include "plane.h"
#include "triangle.h"

#include "geom.h"

using std::cout;
using std::cin;
using std::endl;

int main( )
{
    unsigned N;
    cin >> N;

    std::vector<Triangle> tr;
    std::vector<unsigned> is_intr = {0};

    for (int i = 0; i < N; ++i)
        cin >> tr[i];

    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            is_intr[i] += is_intersect3D(tr[i], tr[j]);

    for (int i = 0; i < N; ++i)
        if (is_intr[i] > 0)
            cout << i << endl;

    return 0;
}