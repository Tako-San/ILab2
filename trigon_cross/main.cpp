#include <iostream>
#include "vec.h"

int main( )
{
    Vec p1(1.1);
    Vec p2(2.3, 3.2, 5.7);
    Vec p3(p2);

    std::cout << "p1 = " << p1 << "\n";
    std::cout << "p2 = " << p2 << "\n";
    std::cout << "p3 = " << p3 << "\n";

    std::cout << "p1 = p2 ? " << (p1 == p2) << "\n";
    std::cout << "p3 = p2 ? " << (p3 == p2) << "\n";

    return 0;
}