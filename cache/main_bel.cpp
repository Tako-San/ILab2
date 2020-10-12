#include "tst_bel.h"

int main( int argc, char ** argv )
{
    unsigned capacity = 0;

    if (argc > 1)
    {
        std::string filename(argv[1]);
        capacity = test_from_file(filename);
        std::cout << "Right answer: " << read_ans(filename) << "\n\n";
    }
    else
        capacity = test_from_console();

    if (capacity == 0)
    {
        std::cout << "Cache capacity is zero\n Exit...\n";
        return 0;
    }

    return 0;
}