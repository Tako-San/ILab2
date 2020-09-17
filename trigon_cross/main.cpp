#include <iostream>
#include "vec.h"

int main( )
{
    Vec p1(1.1);
    Vec p2(2.3, 3.2, 5.7);
    Vec p3(p2);
    Vec p4(0);

    std::cout << "p1: " << p1 << "\n"
              << "p2: " << p2 << "\n"
              << "p3: " << p3 << "\n\n";

    std::cout << "p1 + p2: " << p1 + p2 << "\n"
              << "p2 - p1: " << p2 - p1 << "\n\n";

    std::cout << "p1 == p2 ? " << (p1 == p2) << "\n"
              << "p2 == p3 ? " << (p2 == p3) << "\n\n";

    std::cout << "p4 = p1: " << (p4 = p1) << "\n\n";

    std::cout << "p4 += p1: " << (p4 += p1) << "\n"
              << "p4 -= p1: " << (p4 -= p1) << "\n\n";

    return 0;
}