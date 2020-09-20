/*#include <vector>
#include "cache.h"

int main( int argc, char ** argv )
{
    Cache_t<int, int> lfu(2);

    // for (int i = 0; i < 6; i++)
    //     std::cout << "res: " << lfu.request(i / 2) << ", hsh_sz: " << lfu.hash_tbl.size() << "\n\n";

    for (int i = 0; i < 3; i++)
    {
        // std::cout << "res: " << lfu.request(1) << ", hsh_sz: " << lfu.hash_tbl.size() << "\n";
        // std::cout << "res: " << lfu.request(2) << ", hsh_sz: " << lfu.hash_tbl.size() << "\n";
        lfu.request(1);
        lfu.request(2);
        std::cout << lfu << "\n";
    }

    std::cout << lfu;

    return 0;
}*/


#include <vector>
#include "cache.h"
#include "O_N_cache/O_N_tst.h"

int main( int argc, char ** argv )
{
    std::vector<int> tst_cases;

    unsigned capacity = 0;

    if (argc > 1)
    {
        std::string filename(argv[1]);
        capacity = test_from_file(filename, tst_cases);
        std::cout << "Right answer: " << read_ans(filename) << "\n\n";
    }
    else
        capacity = test_from_console(tst_cases);

    if (capacity == 0)
    {
        std::cout << "Cache capacity is zero\n Exit...\n";
        return 0;
    }

    Cache_t<int> lfu(capacity);

    for (auto call : tst_cases)
        lfu.request(call);

    std::cout << "------------LIST DUMP-----------------------\n";
    std::cout << lfu << "\n";
    std::cout << "Total hits: " << lfu.get_counter() << std::endl;

    return 0;
}