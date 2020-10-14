#include "pair.h"
#include "tree.h"

using std::cout;
using std::endl;

int main()
{
    Tree<Pair<int, int>> t1;

    t1[5] = 50;

    cout << "t[5] = " << t1[5].get_val() << endl;

    return 0;
}