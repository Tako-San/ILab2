#include "tst.h"

unsigned test_from_console( std::vector<int> & tst_cases )
{
    unsigned capacity = 0, calls_amount = 0;

    std::cout << "Input maximum capacity of cache:\n";

    std::cin >> capacity;

    std::cout << "Input amount of calls:\n";

    std::cin >> calls_amount;

    tst_cases.resize(calls_amount);

    for (unsigned i = 0; i < calls_amount; ++i)
    {
        std::cout << "Input request #" << i << "\n";
        std::cin >> tst_cases[i];
    }

    return capacity;
}

unsigned test_from_file( const std::string &filename, std::vector<int> & tst_cases )
{
    std::ifstream test_file(filename);

    if (!test_file.is_open())
    {
        std::cout << "Error with opening file " << filename << "\n";
        return 0;
    }

    unsigned capacity = 0, calls_amount = 0;
    test_file >> capacity >> calls_amount;

    tst_cases.resize(calls_amount);

    for (unsigned i = 0; i < calls_amount; ++i)
        test_file >> tst_cases[i];

    test_file.close();

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