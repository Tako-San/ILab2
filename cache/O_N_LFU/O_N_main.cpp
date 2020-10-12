#include <vector>
#include "O_N_cache.h"
#include "O_N_tst.h"

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
    std::cout << "Hits: " << lfu.get_counter() << std::endl;

    return 0;
}