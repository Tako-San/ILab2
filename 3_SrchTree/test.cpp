#include "pair.h"
#include "node.h"
#include "tree.h"

using std::cout;
using std::endl;

using Pii = Pair<int, int>;

int main()
{
    Tree<Pii> tree1;

    tree1[5] = 50;

    cout << "t[5] = " << tree1[5].get_val() << endl;

    return 0;
}