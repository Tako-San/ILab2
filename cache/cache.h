#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

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
                            cache(0)
    {}

    ~Cache_t( )
    {}

    lst_it request(KeyT key)
    {
        auto search_res = hash_tbl.find(key);

        if (search_res != hash_tbl.end())
        {
            (*search_res).second.call_num++;
            return (*search_res).second.link;
        }
        else
        {
            lst_it res = put_in_cache(key);

            page_info tmp = {res, 1};

            hash_tbl[key] = tmp;

            return res;
        }

    }

    lst_it put_in_cache(KeyT key)
    {
        T tmp = load_from_web(key);
        cache.push_back(tmp);
        return --cache.end();
    }

    T load_from_web(KeyT key)
    {
        return key;
    }

};

#endif //ILAB2_CACHE_H
