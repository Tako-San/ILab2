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

public:
    Cache_t( size_t cap ) : cap(cap),
                            cache(0)
    {}

    ~Cache_t( )
    {}

    T & request( KeyT key )
    {
        auto search_res = hash_tbl.find(key);

        if (search_res != hash_tbl.end())
        {
            search_res->second.hits++;
            counter++;
            //std::cout << "Key: " << key << ", Hits: " << search_res->second.hits << "\n";
            return *(search_res->second.link);
        }
        else
        {
            LstIt link = put_in_cache(key);
            hash_tbl[key] = {link, 0};
            //std::cout << "Key: " << key << ", Hits: 0\n";
            return *link;
        }
    }

private:

    LstIt put_in_cache( KeyT key )
    {
        T data = load_from_web(key);

        if (cache.size() >= cap)
        {
            HshIt deadman = find_loneliest();
            LstIt link = deadman->second.link;

            hash_tbl.erase(deadman);

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

        for (auto it = hash_tbl.begin(); it != end; it++)
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
        {
            while (getline(web, line))
            {
                char * pEnd = nullptr;

                if (strtol(line.c_str(), &pEnd, 10) == key)
                {
                    web.close();
                    return strtol(pEnd, NULL, 10);
                }
            }
        }

        web.close();
        std::cout << "Not found in web, good bye" << std::endl;
        exit(1);

        return key;
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
