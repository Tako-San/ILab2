#include "cache.h"

int main()
{
    // using lst_it = typename std::list<int>::iterator;
    /*Cache_t<int, int> c(4);

    c.request(1); // 1
    c.request(2); // 1
    c.request(3); // 1
    c.request(4); // 1
    c.request(5); // 1


    c.request(1); // 2
    c.request(1); // 3
    c.request(2); // 2
    c.request(2); // 3
    c.request(5); // 2
    c.request(5); // 3

    c.request(6);

    for(const auto& n : c.cache)
        std::cout << "Value: " << n << "\n";

    auto x = c.request(2);

    std::cout << x << std::endl;

    std::cout << c << std::endl;*/

    int hits = 0, capacity = 0, calls_amount = 0;

    std::cout << "Input maximum capacity of cache:\n";

    std::cin >> capacity;

    std::cout << "Input amount of calls:\n";

    std::cin >> calls_amount;

    Cache_t<int> lfu(capacity);

    for (int i = 0; i < calls_amount; ++i)
    {
        int request = 0;
        std::cout << "Input request #" << i << "\n";
        std::cin >> request;

        lfu.request(request);
    }

    std::cout << "Total amounts of hits = " << hits << "\n";
    std::cout << "------------LIST DUMP-----------------------\n";
    std::cout << lfu << "\n";


    return 0;
}