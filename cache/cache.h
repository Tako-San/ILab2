#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

#include <list>
#include <unordered_map>
#include <iostream>

#include <fstream>
#include <string>
#include <cstdlib>

template <typename T, typename KeyT = unsigned long long>
struct Cache_t
{
public:
    unsigned counter = 0;
private:
    using Lst = typename std::list<T>;
    using LstIt = typename std::list<T>::iterator;

    struct PageInfo
    {
        LstIt link;
        size_t hits;
    };

    using Map = typename std::unordered_map<KeyT, PageInfo>;
    using HshIt = typename std::unordered_map<KeyT, PageInfo>::iterator;

    size_t cap;
    Lst cache;
    Map hash_tbl;
    HshIt loneliest;

public:
    explicit Cache_t( size_t cap ) : cap(cap),
                            cache(0),
                            loneliest(hash_tbl.end())
    {}

    T & request( KeyT key )
    {
#define INCREMENT_AND_RETURN( )        \
                                       \
    search_res->second.hits++;         \
    counter++;                         \
    return *(search_res->second.link)  \


        HshIt search_res = hash_tbl.find(key);

        if (search_res == hash_tbl.end())
        {
            LstIt link = put_in_cache(key);
            hash_tbl[key] = {link, 0};
            loneliest = hash_tbl.find(key);
            return *link;
        }
        else if (search_res == loneliest )
        {
            loneliest = find_loneliest();
            INCREMENT_AND_RETURN();
        }
        else if (search_res != hash_tbl.end())
        {
            INCREMENT_AND_RETURN();
        }
        else
        {
            std::cout << "Unknown hash iterator.\n";
            std::cout << "Exit...\n";
            exit(1);
        }

#undef INCREMENT_AND_RETURN
    }

private:

    LstIt put_in_cache( KeyT key )
    {
        T data = load_from_web(key);

        if (cache.size() >= cap)
        {
            LstIt link = loneliest->second.link;
            hash_tbl.erase(loneliest);
            *link = data;
            return link;
        }

        cache.push_front(data);
        return cache.begin();
    }

    HshIt find_loneliest( )
    {
        if (hash_tbl.empty())
        {
            std::cout << "Hash table is empty\n";
            exit(1);
        }

        HshIt end = hash_tbl.end(),
              min = hash_tbl.begin();

        for (HshIt it = hash_tbl.begin(); it != end; it++)
            if (it->second.hits < min->second.hits)
                min = it;

        return min;
    }


    T load_from_web( KeyT key )
    {
        std::string line;
        std::ifstream web;

        web.open("/media/hdd/my_data/ILab2/cache/web.txt");

        if (web.is_open())
            while (getline(web, line))
            {
                char * pEnd = nullptr;

                if (strtol(line.c_str(), &pEnd, 10) == key)
                {
                    web.close();
                    return strtol(pEnd, nullptr, 10);
                }
            }

        web.close();
        std::cout << "Not found in web, good bye" << std::endl;
        exit(1);
    }

    template <typename Tp, typename KeyTp>
    friend std::ostream & operator <<( std::ostream &, const Cache_t<Tp, KeyTp> & );
};


template <typename T, typename KeyT>
std::ostream & operator <<( std::ostream & ost, const Cache_t<T, KeyT> & unit )
{
    for (auto & elem : unit.hash_tbl)
        ost << "Key: " << elem.first << ", Val: " <<
               *(elem.second.link) << ", Hits: " <<
               elem.second.hits << std::endl;

    return ost;
}

#endif //ILAB2_CACHE_H
