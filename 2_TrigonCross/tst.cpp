#include <iostream>

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
    // Vectors

    /*Vec v1{1, 0, 0};
    Vec v2{1};
    Vec v3{v1};
    Vec v4{0, 1, 0};

    cout << "VECTORS:" << endl;
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "v3: " << v3 << endl;
    cout << "v4: " << v4 << endl << endl;

    cout << "v1 == v2? " << (v1 == v2 ? 'y' : 'n') << endl;
    cout << "v1 == v3? " << (v1 == v3 ? 'y' : 'n') << endl << endl;

    cout << "v1 != v2? " << (v1 != v2 ? 'y' : 'n') << endl;
    cout << "v1 != v3? " << (v1 != v3 ? 'y' : 'n') << endl << endl;

    cout << "v2.normalise(): " << v2.normalise() << endl;
    cout << "v1.normalise(): " << v1.normalise() << endl << endl;

    cout << "v1 += v3: " << (v1 += v3) << endl;
    cout << "v1 -= v3: " << (v1 -= v3) << endl << endl;

    cout << "v1 *= 2: " << (v1 *= 2) << endl;
    cout << "v1 /= 2: " << (v1 /= 2) << endl << endl;

    cout << "v2 = v1: " << (v2 = v1) << endl;
    cout << "-v2: " << -v2 << endl << endl;

    cout << "v1[X] = " << v1[X] << endl;
    cout << "v1[Y] = " << v1[Y] << endl;
    cout << "v1[Z] = " << v1[Z] << endl << endl;

    cout << "!v1 = " << !v1 << endl << endl;

    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl << endl;

    cout << "4 * v1 = " << 4 * v1 << endl;
    cout << "v1 * 4 = " << v1 * 4 << endl << endl;

    cout << "v1 & v4 = " << (v1 & v4) << endl;
    cout << "v1 % v4 = " << (v1 % v4) << endl << endl;


    // Lines
    Line l1{v1, v4};
    Line l2{l1};

    cout << "LINES:" << endl;

    cout << "l1: " << l1 << endl;
    cout << "l2: " << l2 << endl << endl;


    // Planes
    Plane pl1{v1, 0};
    Plane pl2{pl1};
    Plane pl3{v1, v4};
    Plane pl4{Vec{1, 0, 0}, Vec{0, 1, 0}, Vec{0, 0, 1}};

    cout << "PLANES:" << endl;

    cout << "pl1: " << pl1 << endl;
    cout << "pl2: " << pl2 << endl;
    cout << "pl3: " << pl3 << endl;
    cout << "pl4: " << pl4 << endl << endl;*/


    // Triangle
    Triangle tr1{Vec{1, 0, 0}, Vec{0, 1,  0}, Vec{0, 0, 1}};
    Triangle tr2{Vec{0, 0, 1}, Vec{0, 0, -1}, Vec{1, 1, 0}};

    cout << "intersect?\n" << (is_intersect3D(tr1, tr2) ? "YES" : "NO") << endl;

    return 0;
}
