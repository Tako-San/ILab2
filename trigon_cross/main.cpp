#include <iostream>
#include "vec.h"

using std::cout;
using std::cin;
using std::endl;

int main( )
{
    Vec p1(1.1);
    Vec p2(2.3, 3.2, 5.7);
    Vec p3(p2);
    Vec p4(0);

    cout << "p1: " << p1 << "\n"
         << "p2: " << p2 << "\n"
         << "p3: " << p3 << "\n\n";

    cout << "p1 + p2: " << p1 + p2 << "\n"
         << "p2 - p1: " << p2 - p1 << "\n\n";

    cout << "p1 == p2 ? " << (p1 == p2) << "\n"
         << "p2 == p3 ? " << (p2 == p3) << "\n\n";

    cout << "p4 = p1: " << (p4 = p1) << "\n\n";

    cout << "p4 += p1: " << (p4 += p1) << "\n"
         << "p4 -= p1: " << (p4 -= p1) << "\n\n";

    cout << "p1 * 4: " << p1 * 4 << "\n"
         << "4 * p1: " << 4 * p1 << "\n"
         << "p1: " << p1 << "\n\n";

    Vec p5 = p1 * 4;

    cout << "p5: " << p5 << endl;

    return 0;
}