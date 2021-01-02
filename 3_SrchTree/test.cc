#include <iostream>
#include <cassert>
#include "node.hh"
#include "tree.hh"


using namespace F;

using std::cin;
using std::cout;
using std::endl;

const char DOT[]  = "../dump/dump.dot";
const char PLOT[] = "../dump/dump.png";

int main( )
{
    Tree<int> tree{};

    for (int i = 0; i < 6; ++i)
        tree.insert(i);

    for (int i = 0; i < 4; ++i)
    {
        cout << "#" << i << ":\n";
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
    cout << "\n\n";

    tree.dump(DOT, PLOT);
    tree.print_leafs();

    return 0;
}