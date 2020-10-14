#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

#include <list>
#include <unordered_map>
#include <iostream>

#include <fstream>
#include <string>
#include <cstdlib>

template <typename T, typename KeyT = long long int>
struct Cache_t
{
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

    unsigned counter;
    size_t cap;

    Lst cache;
    Map hash_tbl;

    HshIt loneliest;

public:
    explicit Cache_t( size_t cap ) : counter(0),
                                     cap(cap),
                                     cache(0),
                                     loneliest(hash_tbl.end())
    {}

    T & request( KeyT key )
    {
        if (hash_tbl.empty())
        {
            LstIt link = put_in_cache(key);
            hash_tbl[key] = {link, 0};

            loneliest = hash_tbl.find(key);

            return *link;
        }

        HshIt search_res = hash_tbl.find(key);

        if (search_res == hash_tbl.end())
        {
            LstIt link = put_in_cache(key);
            hash_tbl[key] = {link, 0};

            loneliest = hash_tbl.find(key);

            return *link;
        }
        else if (search_res == loneliest)
        {
            search_res->second.hits++;
            counter++;

            loneliest = find_loneliest();
            return *(search_res->second.link);
        }
        else if (search_res != hash_tbl.end())
        {
            search_res->second.hits++;
            counter++;

            return *(search_res->second.link);
        }
        else
        {
            std::cout << "Unknown hash iterator.\n";
            std::cout << "Exit...\n";
            exit(1);
        }
    }

    unsigned get_counter( )
    {
        return counter;
    }

private:
    LstIt put_in_cache( KeyT key )
    {
        T data = load_from_web(key);

        if (cache.size() >= cap)
        {
            LstIt link = loneliest->second.link;
            *link = data;

            hash_tbl.erase(loneliest);
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

        for (HshIt it = min; it != end; ++it)
            if (it->second.hits < min->second.hits)
                min = it;

        return min;
    }


    T load_from_web( KeyT key )
    {
        return key;

        /*std::string line;
        std::ifstream web;

        web.open("/media/hdd/my_data/ILab2/1_Cache/web.txt");

        if (!web.is_open())
        {
            web.close();
            std::cout << "Web is not availible" << std::endl;
            exit(1);
        }

        while (getline(web, line))
        {
            char * pEnd = nullptr;

            if (strtoll(line.c_str(), &pEnd, 10) == key)
            {
                web.close();
                return strtoll(pEnd, nullptr, 10);
            }
        }

        web.close();
        std::cout << "Not found in web, good bye" << std::endl;
        exit(1);*/
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
