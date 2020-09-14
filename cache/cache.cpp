#include "cache.h"

int main()
{
    using lst_it = typename std::list<int>::iterator;
    Cache_t<int, int> c(4);

    c.put_in_cache(1);
    c.put_in_cache(2);
    c.put_in_cache(3);
    c.put_in_cache(4);

    for( const auto& n : c.cache )
    {
        std::cout << "Value: " << n << "\n";
    }

    lst_it x = c.request(2);

    std::cout << *x << std::endl;

    return 0;
}