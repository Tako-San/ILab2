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

using std::chrono::microseconds;
using std::chrono::high_resolution_clock;


int main( )
{
    // reading keys
    int key_num = 0;
    cin >> key_num;

    std::vector<int> keys;
    keys.resize(key_num);

    for (int i = 0; i < key_num; ++i)
        cin >> keys[i];

    // readig requests
    int req_num = 0;
    cin >> req_num;

    std::vector<int> requests;
    requests.resize(req_num * 2);

    for (int i = 0; i < req_num * 2; i += 2)
        cin >> requests[i] >> requests[i + 1];

    // std::set

    cout << "std::set\nANS: ";

    auto begin = high_resolution_clock::now();

    set<int> std_tree{};

    for(auto key : keys)
        std_tree.insert(key);

    for (int i = 0; i < req_num * 2; i += 2)
    {
        auto tree_it = std_tree.lower_bound(requests[i]);

        if (tree_it == std_tree.end())
        {
            cout << 0 << " ";
            continue;
        }

        int counter = 0;

        while (*tree_it <= requests[i + 1])
        {
            ++counter;
            ++tree_it;
        }

        cout << counter << " ";
    }

    auto end = high_resolution_clock::now();

    cout << "\nTIME: " << duration_cast<microseconds>(end - begin).count() << " ms\n";


    // my tree

    cout << "\nF::Tree\nANS: ";

    auto begin2 = high_resolution_clock::now();

    F::Tree<int> my_tree{};

    for(auto key : keys)
        my_tree.insert(key);

    for (int i = 0; i < req_num * 2; i += 2)
    {
        auto tree_it = my_tree.lower_bound(requests[i]);

        if (tree_it == my_tree.end())
        {
            cout << 0 << " ";
            continue;
        }

        int counter = 0;

        while (*tree_it <= requests[i + 1])
        {
            ++counter;
            ++tree_it;
        }

        cout << counter << " ";
    }

    auto end2 = high_resolution_clock::now();

    cout << "\nTIME: " << duration_cast<microseconds>(end2 - begin2).count() << " ms\n";

    return 0;
}