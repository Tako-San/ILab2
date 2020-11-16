#include <iostream>
#include <cassert>
#include "node.hh"
#include "tree.hh"


using namespace F;

using std::cin;
using std::cout;
using std::endl;

int main( )
{
    Tree<int> tree{};

    for (int i = 0; i < 32; ++i)
        tree.insert(i);

    for (int i = 0; i < 6; ++i)
    {
        cout << "#" << i << ": ";
        tree.print_lvl(i);
        cout << endl;
    }

    return 0;
};