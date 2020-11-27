#include <iostream>
#include <vector>

#include "tree.hh"


using std::cin;
using std::cout;
using std::endl;


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

    for (int i = 0; i < req_num; ++i)
        cin >> requests[2 * i] >> requests[2 * i + 1];

    F::Tree<int> my_tree{};

    for(auto key : keys)
        my_tree.insert(key);

    for (int i = 0; i < req_num; ++i)
    {
        auto tree_it = my_tree.lower_bound(requests[2 * i]);
        auto end_it = my_tree.end();
        if (tree_it == end_it)
        {
            cout << 0 << " ";
            continue;
        }

        int counter = 0;

        while ( (tree_it != end_it) && (*tree_it <= requests[2 * i + 1]))
        {
            ++counter;
            ++tree_it;
        }

        cout << counter << " ";
    }

    return 0;
}