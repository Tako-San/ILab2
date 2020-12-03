#ifndef SRCH_TREE_NEC_HH
#define SRCH_TREE_NEC_HH

#include <iostream>
#include <vector>
#include <chrono>

using std::vector;

using std::cin;
using std::cout;
using std::endl;


using std::chrono::microseconds;
using std::chrono::high_resolution_clock;

extern int key_num;
extern int req_num;
extern vector<int> keys;
extern vector<int> requests;

#include <getopt.h>

enum FLAGS
{
    C = 1u,
    I = 1u << 1u,
    D = 1u << 2u
};

enum OP_CODE
{
    END     = -1,
    UNKNOWN = -2
};

const char SHORT_OPTS[] = "icdh";

struct option OPTS[] =
        {
                {"compare", 0, nullptr, 'c'},
                {"insert_uncount", 0, nullptr, 'i'},
                {"dump", 0, nullptr, 'd'},
                {"help", 0, nullptr, 'h'},
                {nullptr, 0, nullptr, 0}
        };

uint read_opts(int ac, char ** av)
{
    int cur_opt = 0;
    uint opts   = 0x0u;

    while (true)
    {
        cur_opt = getopt_long(ac, av, SHORT_OPTS, OPTS, nullptr);

        switch (cur_opt)
        {
            case '?':
                std::cerr << "Unknown key\n";
                return UNKNOWN;
            case 'i':
                opts |= I;
                break;
            case 'c':
                opts |= C;
                break;
            case 'd':
                opts |= D;
                break;
            case 'h':
                std::cerr << "USAGE: ./tree [-c] [-d] [-i]\n";
                exit(0);
            case END:
                return opts;
            default:
                return UNKNOWN;
        }
    }
}

template <typename Tree>
void testing_tree( Tree & tree, uint opts )
{
    bool inst = opts & I,
         comp = opts & C;

    auto begin = high_resolution_clock::now();

    for(auto key : keys)
        tree.insert(key);

    if (inst)
        begin = high_resolution_clock::now();

    for (int i = 0; i < req_num; ++i)
    {
        auto tree_it = tree.lower_bound(requests[2 * i]),
                end_it  = tree.end();

        if (tree_it == tree.end())
        {
            if (!comp)
                cout << 0 << " ";
            continue;
        }

        int counter = 0;

        while ((tree_it != end_it) && (*tree_it <= requests[2 * i + 1]))
        {
            ++counter;
            ++tree_it;
        }

        if (!comp)
            cout << counter << " ";
    }

    auto end = high_resolution_clock::now();

    cout << endl;

    if (comp)
        cout << "TIME: " << duration_cast<microseconds>(end - begin).count() << " mcs\n";
}

#endif //SRCH_TREE_NEC_HH
