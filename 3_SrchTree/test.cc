#include <vector>
#include "my_pair/pair.h"
#include "tree.hh"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;


int main( )
{
    Tree<int> tree;

    uint num{};
    cout << "Input elem num: ";
    cin >> num;

    vector<int> elems{};
    elems.resize(num);

    for (uint i = 0; i < num; ++i)
    {
        cin >> elems[i];
        tree.add(elems[i]);
    }

    for (uint i = 0; i < num; ++i)
    {
        cout << "t[" << elems[i] << "] = ";
        cout << *(tree.find(elems[i])) << ";" << endl;
    }

    cout << endl;
    tree.print();

    return 0;
}


/*int main( )
{
    Tree<Pair<int, int>> t1;

    int key{};
    int val{};

    unsigned num{};

    cout << "Input elem num: ";
    cin >> num;

    vector<int> keys{};

    for (unsigned i = 0; i < num; ++i)
    {
        cout << "Input key: ";
        cin >> key;

        keys.push_back(key);

        cout << "Input val: ";
        cin >> val;

        t1.add({key, val});
    }

    for (auto & cur_key : keys)
    {
        cout << "t[" << cur_key << "] = " << t1.find(cur_key).get_val() << ";" << endl;
    }

    return 0;
}*/