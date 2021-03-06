#include <iostream>
#include <vector>
#include <set>

#include "nec.hh"
#include "tree.hh"

using std::set;

const char DOT[]  = "../dump/dump.dot";
const char PLOT[] = "../dump/dump.png";

int key_num;
int req_num;
vector<int> keys;
vector<int> requests;


int main( int ac, char ** av )
{
    uint opts = read_opts(ac, av);

    bool comp = opts & C,
         dump = opts & D;

    cin >> key_num;
    keys.resize(key_num);

    for (int i = 0; i < key_num; ++i)
        cin >> keys[i];

    // readig requests
    cin >> req_num;
    requests.resize(req_num * 2);

    for (int i = 0; i < req_num; ++i)
        cin >> requests[2 * i] >> requests[2 * i + 1];

    // std::set
    if (comp)
    {
        set<int> std_tree{};
        cout << "std::set\n";
        testing_tree(std_tree, opts);
    }


    // my tree
    F::Tree<int> my_tree{};
    if (comp)
        cout << "\nF::Tree\n";
    testing_tree(my_tree, opts);

    // print my tree to png
    my_tree.remove(0);
    if (dump)
        my_tree.dump(DOT, PLOT);

    return 0;
}
