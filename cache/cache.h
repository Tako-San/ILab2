#ifndef ILAB2_CACHE_V1_5_H
#define ILAB2_CACHE_V1_5_H

#include <list>
#include <unordered_map>
#include <iostream>

template <typename T, typename KeyT = unsigned long long>
struct Cache_t
{
    using lst_it = typename std::list<T>::iterator;

    struct page_info
    {
        lst_it link;
        size_t call_num;
    };

    using u_map = typename std::unordered_map<KeyT, page_info>;

    size_t cap;
    std::list<T> cache;
    u_map hash_tbl;

    Cache_t( size_t cap ) : cap(cap),
                            cache(cap)
    {}

    ~Cache_t( )
    {}

    lst_it request()
    {

    }

};

#endif //ILAB2_CACHE_V1_5_H
