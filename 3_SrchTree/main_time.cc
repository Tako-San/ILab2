#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <set>

#include "tree.hh"

using std::set;

using std::cin;
using std::cout;
using std::endl;

using std::vector;

using std::chrono::microseconds;
using std::chrono::high_resolution_clock;

int key_num;
int req_num;
vector<int> keys;
vector<int> requests;

template <typename Tree>
void testing_tree( Tree & tree )
{
    auto begin = high_resolution_clock::now();

    for(auto key : keys)
        tree.insert(key);

    for (int i = 0; i < req_num; ++i)
    {
        auto tree_it = tree.lower_bound(requests[2 * i]);
        auto end_it = tree.end();

        if (tree_it == tree.end())
        {
            cout << 0 << " ";
            continue;
        }

        int counter = 0;

        while ((tree_it != end_it) && (*tree_it <= requests[2 * i + 1]))
        {
            ++counter;
            ++tree_it;
        }

        cout << counter << " ";
    }

    auto end = high_resolution_clock::now();

    cout << "\nTIME: " << duration_cast<microseconds>(end - begin).count() << " ms\n";
}

int main( )
{
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
    set<int> std_tree{};
    cout << "std::set\nANS: ";
    testing_tree(std_tree);


    // my tree

    F::Tree<int> my_tree{};
    cout << "\nF::Tree\nANS: ";
    testing_tree(my_tree);

    return 0;
}