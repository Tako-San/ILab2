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

    for (int i = 0; i < 511; ++i)
        tree.insert(i);

    for (int i = 0; i < 9; ++i)
    {
        cout << "#" << i << ": ";
        tree.print_lvl(i);
        cout << endl;
    }

    auto triter = tree.begin(),
         end = tree.end();

    while (triter != end)
    {
        cout << *triter << " ";
        ++triter;
    }

    cout << endl;

    return 0;
}