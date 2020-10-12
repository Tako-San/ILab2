#include "tst_lfu.h"
#include "cache.h"

unsigned test_from_console( )
{
    unsigned capacity = 0, calls_amount = 0;

    std::cout << "Input maximum capacity of cache:\n";

    std::cin >> capacity;

    if (capacity == 0)
        return capacity;

    std::cout << "Input amount of calls:\n";

    std::cin >> calls_amount;

    Cache_t<int, int> LFU(capacity);

    for (unsigned i = 0; i < calls_amount; ++i)
    {
        int tmp;
        std::cout << "Input request #" << i << "\n";
        std::cin >> tmp;
        LFU.request(tmp);
    }

    LFU.dump();

    return capacity;
}

unsigned test_from_file( const std::string &filename )
{
    std::ifstream test_file(filename);

    if (!test_file.is_open())
    {
        std::cout << "Error with opening file " << filename << "\n";
        return 0;
    }

    unsigned capacity = 0, calls_amount = 0;
    test_file >> capacity >> calls_amount;

    if (capacity == 0)
        return capacity;

    Cache_t<int, int> LFU(capacity);

    for (unsigned i = 0; i < calls_amount; ++i)
    {
        int tmp;
        test_file >> tmp;
        LFU.request(tmp);
    }

    test_file.close();
    LFU.dump();

    return capacity;
}

unsigned read_ans( const std::string & filename )
{
    std::string fn(filename);
    fn.replace(fn.end() - 3, fn.end(), "ans");

    std::ifstream ans_file(fn);

    if (!ans_file.is_open())
    {
        std::cout << "Error with opening file " << fn << "\n";
        return 0;
    }

    unsigned ans = 0;

    ans_file >> ans;

    ans_file.close();

    return ans;
}